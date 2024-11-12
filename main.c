#include <stdio.h>
#include <stdlib.h>
#include "loc.h"
#include "moves.h"
#include "prob_mov.h"
#include "stack.h"
#include "queue.h"
#include "map.h"
#include "n_ary_tree.h"

#include "map.h"

int main() {
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

    // Initialiser les mouvements sélectionnés
    t_move selected_moves[SEL_MOV];

    // Réinitialiser les probabilités
    resetProbabilities();

    // Afficher les probabilités initiales
    printf("Probabilités initiales :\n");
    printProbabilities(move_probabilities, NUM_MOV);

    // Choisir les mouvements
    chooseMoves(selected_moves);

    // Afficher les mouvements sélectionnés
    printf("\nMouvements sélectionnés:\n");
    for (int i = 0; i < SEL_MOV; i++) {
        printf("Mouvement %d sélectionné\n", selected_moves[i]);
    }

    // Afficher les probabilités après sélection
    printf("\nProbabilités après sélection:\n");
    printProbabilities(move_probabilities, NUM_MOV);

    // Appeler la fonction shuffle pour mélanger les probabilités
    shuffle(move_probabilities, NUM_MOV);

    // Afficher les probabilités après mélange
    printf("\nProbabilités après mélange:\n");
    printProbabilities(move_probabilities, NUM_MOV);

    // Créer un arbre n-aire et construire un arbre simple
    t_node* root = NULL;
    build_simple_tree(&root);
    // Afficher la structure de l'arbre pour vérifier la construction
    printf("Racine: Position (%d, %d), Total Cost: %d\n", root->pos.x, root->pos.y, root->totalCost);
    for (int i = 0; i < root->numChildren; i++)
    {
        printf("Enfant %d: Position (%d, %d), Total Cost: %d, Type de sol: %d\n", i + 1,
               root->children[i]->pos.x, root->children[i]->pos.y,
               root->children[i]->totalCost, root->children[i]->soilType);
    }

    return 0;
}
