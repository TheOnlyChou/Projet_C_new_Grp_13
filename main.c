#include <stdio.h>
#include <stdlib.h>
#include "loc.h"
#include "moves.h"
#include "prob_mov.h"
#include "stack.h"
#include "queue.h"
#include "map.h"

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

    t_move selected_moves[SEL_MOV];
    
    resetProbabilities();
    
    printf("Probabilités initiales :\n");
    printProbabilities(move_probabilities, NUM_MOV);

    chooseMoves(selected_moves);

    printf("\nMouvements sélectionnés:\n");
    for (int i = 0; i < SEL_MOV; i++) 
    {
        printf("Mouvement %d sélectionné\n", selected_moves[i]);
    }

    printf("\nProbabilités après sélection:\n");
    printProbabilities(move_probabilities, NUM_MOV);
    
    return 0;
}
