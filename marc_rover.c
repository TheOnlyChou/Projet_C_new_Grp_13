//
// Created by alex8 on 22/11/2024.
//
#include <stdio.h>

#include "marc_rover.h"

t_marc_rover createMarcRover(t_localisation loc, int total_cost, t_tree tree)
{
    t_marc_rover marc_rover;
    marc_rover.loc = loc;
    marc_rover.total_cost = total_cost;

    // Initialiser les mouvements aléatoires
    t_move random_moves[9];
    chooseNineMoves(random_moves);

    // Choisir les mouvements parmi les 9
    t_move selected_moves[SEL_MOV];
    chooseMoves(selected_moves);

    // Copier les mouvements sélectionnés dans la structure du robot
    for (int i = 0; i < SEL_MOV; i++)
    {
        marc_rover.choose_Moves[i].move = selected_moves[i];
        for (int j = 0; j < NUM_MOV; j++)
        {
            if (move_probabilities[j].move == selected_moves[i])
            {
                marc_rover.choose_Moves[i].probability = move_probabilities[j].probability;
                break;
            }
        }
    }

    marc_rover.tree = tree;
    return marc_rover;
}

void freeMarcRover(t_marc_rover *marc_rover)
{
    freeTree(marc_rover->tree.root);
}

void displayMarcRover(t_marc_rover marc_rover)
{
    printf("\nRobot MARC\n");
    printf("Localisation : (%d, %d)\n", marc_rover.loc.pos.x, marc_rover.loc.pos.y);
    printf("Orientation : %d\n", marc_rover.loc.ori); // 0 = NORTH, 1 = EAST, 2 = SOUTH, 3 = WEST
    printf("Coût total : %d\n", marc_rover.total_cost); // Coût total du parcours
    printf("Mouvements aléatoires sélectionnés :\n");
    for (int i = 0; i < SEL_MOV; i++)
    {
        printf("Mouvement %d : %d (probabilité : %.2f)\n", i, marc_rover.choose_Moves[i].move, marc_rover.choose_Moves[i].probability);
    }
    displayNaryTree(marc_rover.tree.root);
}

void decreaseActions(t_marc_rover *marc_rover, int action)
{
    if (action < 0 || action >= SEL_MOV)
    {
        printf("Action invalide.\n");
        return;
    }

    t_move new_move = selectMove();
    marc_rover->choose_Moves[action].move = new_move;

    for (int i = 0; i < NUM_MOV; i++)
    {
        if (move_probabilities[i].move == new_move)
        {
            marc_rover->choose_Moves[action].probability = move_probabilities[i].probability;
            break;
        }
    }

    printProbabilities(move_probabilities, NUM_MOV);
}
