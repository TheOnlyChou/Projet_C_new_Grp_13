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
    printf("Probabilités initiales :\n");
    printProbabilities(move_probabilities, NUM_MOV);
    printf("\n");

    // Sélection et affichage des mouvements
    t_move selected_moves[SEL_MOV];
    chooseMoves(selected_moves);
    printf("Mouvements sélectionnés :\n");
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
    printf("\nSimuler une phase de déplacement avec arbre N-aire :\n");
    createTree(&map, &move_tree, &marc_rover);

    // Affichage des informations du rover après création de l'arbre
    displayMarcRover(marc_rover);

    // Tester les terrains spéciaux (ERG, REG, CREVASSE)
    printf("\nTester les terrains spéciaux :\n");
    t_localisation test_loc = loc_init(1, 1, NORTH); // Emplacement fictif pour test
    marc_rover.loc = test_loc;

    t_soil test_soil = map.soils[marc_rover.loc.pos.y][marc_rover.loc.pos.x];
    printf("Terrain actuel : %d\n", test_soil);

    if (test_soil == REG)
    {
        printf("Terrain REG détecté. Réduction à 4 mouvements disponibles.\n");
        createTree(&map, &move_tree, &marc_rover);
    }
    else if (test_soil == ERG)
    {
        printf("Terrain ERG détecté. Ajustement des coûts de déplacement.\n");
        createTree(&map, &move_tree, &marc_rover);
    }
    else if (test_soil == CREVASSE)
    {
        printf("Attention : terrain CREVASSE détecté. Mouvement impossible !\n");
    }

    // Afficher à nouveau le rover après interaction avec terrains spéciaux
    displayMarcRover(marc_rover);

    // Libération des ressources
    printf("\nLibération des ressources...\n");
    freeMarcRover(&marc_rover);
    printf("Terminé.\n");

    return 0;
}
