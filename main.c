#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    srand(time(NULL)); // Initialiser la graine du générateur de nombres aléatoires

    t_move selected_moves[SEL_MOV];
    chooseMoves(selected_moves);

    // Afficher les mouvements sélectionnés
    for (int i = 0; i < SEL_MOV; i++) {
        printf("Mouvement %d : %d\n", i, selected_moves[i]);
    }

    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    // Initialiser les probabilités de mouvement
    resetProbabilities();
    printf("\nProbabilités initiales :\n");
    printProbabilities(move_probabilities, NUM_MOV);

    // Choisir des mouvements et afficher
    chooseMoves(selected_moves);
    printf("\nMouvements sélectionnés :\n");
    for (int i = 0; i < SEL_MOV; i++) {
        printf("\nMouvement %d sélectionné\n", selected_moves[i]);
    }

    // Initialiser la localisation du robot
    t_localisation loc = { {0, 0}, 0 }; // Position (0,0) et orientation NORTH

    // Initialiser le coût total
    int total_cost = 0;

    // Initialiser les mouvements aléatoires
    t_move random_moves[9];
    chooseNineMoves(random_moves);

    // Initialiser l'arbre n-aire
    t_tree tree;
    t_move_probability move_p = {0}; // Example initialization, replace with actual data
    t_soil TypeSoil = {0}; // Example initialization, replace with actual data
    int cost_move = 0; // Example initialization, replace with actual data
    tree.root = createNode(move_p, TypeSoil, cost_move);

    // Créer le robot MARC
    t_marc_rover marc_rover = createMarcRover(loc, total_cost, random_moves, tree);

    // Afficher le robot MARC
    displayMarcRover(marc_rover);

    // Diminuer une action spécifique (par exemple, l'action 0)
    decreaseActions(&marc_rover, 0);

    // Libérer la mémoire allouée pour le robot MARC
    freeMarcRover(&marc_rover);

    return 0;
}