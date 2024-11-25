#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "loc.h"
#include "moves.h"
#include "prob_mov.h"
#include "stack.h"
#include "queue.h"
#include "map.h"
#include "n_ary_tree.h"
#include "marc_rover.h"

int main()
{
    srand(time(NULL));

    // Chargement de la carte avec gestion des chemins Windows/Linux
    t_map map;

    // Vérification du système pour le chemin d'accès au fichier
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);

    // Affichage des types de sols de la carte
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }

    // Affichage des coûts de déplacement, alignés à gauche
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }

    // Affichage graphique de la carte
    displayMap(map);
    printf("\n");

    // Initialisation des probabilités de mouvement
    resetProbabilities();
    printf("Probabilites initiales :\n");
    printProbabilities(move_probabilities, NUM_MOV);
    printf("\n");

    // Sélection et affichage des mouvements
    t_move selected_moves[SEL_MOV];
    chooseMoves(selected_moves);
    printf("Mouvements selectionnes :\n");
    for (int i = 0; i < SEL_MOV; i++)
    {
        printf("Mouvement %d : %s\n", i, getMoveAsString(selected_moves[i]));
    }
    printf("\n");

    // Initialisation du rover MARC
    t_localisation start_loc = loc_init(0, 0, NORTH); // Départ en (0,0), orienté Nord
    t_tree move_tree = createEmptyTree();
    t_marc_rover marc_rover = createMarcRover(start_loc, 0, move_tree);
    printf("Rover MARC initialisé.\n");

    // Simulation d'une phase de déplacement avec l'arbre N-aire
    printf("\nSimuler une phase de deplacement avec arbre N-aire :\n");
    createTree(&map, &move_tree, &marc_rover);

    // Affichage des informations du rover après création de l'arbre
    displayMarcRover(marc_rover);

    // Tester les terrains spéciaux (ERG, REG, CREVASSE)
    printf("\nTester les terrains speciaux :\n");
    t_localisation test_loc = loc_init(1, 1, NORTH); // Emplacement fictif pour test
    marc_rover.loc = test_loc;

    t_soil test_soil = map.soils[marc_rover.loc.pos.y][marc_rover.loc.pos.x];
    printf("Terrain actuel : %d\n", test_soil);

    if (test_soil == REG)
    {
        printf("Terrain REG détecte. Reduction à 4 mouvements disponibles.\n");
        createTree(&map, &move_tree, &marc_rover);
    }
    else if (test_soil == ERG)
    {
        printf("Terrain ERG détecté. Ajustement des coûts de deplacement.\n");
        createTree(&map, &move_tree, &marc_rover);
    }
    else if (test_soil == CREVASSE)
    {
        printf("Attention : terrain CREVASSE detecte. Mouvement impossible !\n");
    }

    // Afficher à nouveau le rover après interaction avec terrains spéciaux
    displayMarcRover(marc_rover);

    // Utilisation des nouvelles fonctions
    printf("\nUtilisation des nouvelles fonctions :\n");

    // Trouver la feuille avec le coût minimal
    t_node *min_leaf = findMinLeaf(&move_tree);
    if (min_leaf != NULL)
    {
        printf("Feuille avec le cout minimal trouvee.\n");

        // Générer le chemin à partir de la feuille trouvée
        int pathLength, totalCost;
        int *path = generatePath(min_leaf, &pathLength, &totalCost);
        printf("Chemin genere avec longueur %d et cout total %d.\n", pathLength, totalCost);

        // Afficher la carte avec la position du rover
        renderMap(&map, marc_rover.loc.pos);

        // Diriger le rover en évitant le chemin
        directRover(&marc_rover, path, pathLength);

        // Suivre le chemin généré
        followPath(&map, &marc_rover, path, pathLength);

        // Libérer la mémoire du chemin
        free(path);
    }
    else
    {
        printf("Aucune feuille trouvee avec un coût minimal.\n");
    }

    // Libération des ressources
    printf("\nLiberation des ressources...\n");
    freeMarcRover(&marc_rover);
    printf("Termine.\n");

    return 0;
}
