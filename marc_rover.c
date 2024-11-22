//
// Created by alex8 on 22/11/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "marc_rover.h"
#include "n_ary_tree.h"
#include "prob_mov.h"

t_marc_rover createMarcRover(t_localisation loc, int total_cost, t_move_probability choose_Moves[9], t_tree tree)
{
    t_marc_rover marc_rover;
    marc_rover.loc = loc;
    marc_rover.total_cost = total_cost;
    for (int i = 0; i < 9; i++)
    {
        marc_rover.choose_Moves[i] = choose_Moves[i];
    }
    marc_rover.tree = tree;
    return marc_rover;
}

void freeMarcRover(t_marc_rover *marc_rover)
{
    freeTree(marc_rover->tree.root);
    return;
}

void displayMarcRover(t_marc_rover marc_rover)
{
    printf("\nRobot MARC\n");
    printf("Localisation : (%d, %d)\n", marc_rover.loc.pos.x, marc_rover.loc.pos.y);
    printf("Orientation : %d\n", marc_rover.loc.ori); // 0 = NORTH, 1 = EAST, 2 = SOUTH, 3 = WEST
    printf("Coût total : %d\n", marc_rover.total_cost); // Coût total du parcours
    printf("Mouvements aléatoires sélectionnés :\n");
    for (int i = 0; i < 9; i++)
    {
        printf("Mouvement %d : %d\n", i, marc_rover.choose_Moves[i]);
    }
    printf("Arbre n-aire du robot MARC :\n");
    displayNaryTree(marc_rover.tree.root);
    return;
}

void decreaseActions(t_marc_rover *marc_rover, int action)
{
    // Vérifier que l'action est bien entre 0 et 8 (9 mouvements possibles)
    if (action < 0 || action >= 9)
    {
        printf("Action invalide.\n");
        return;
    }

    // Utiliser la fonction selectMove pour choisir un mouvement
    t_move new_move = selectMove();

    // Remplacer l'action actuelle par le nouveau mouvement sélectionné
    marc_rover->choose_Moves[action].move = new_move;

    // Mettre à jour la probabilité associée au mouvement choisi
    for (int i = 0; i < NUM_MOV; i++)
    {
        if (move_probabilities[i].move == new_move)
        {
            marc_rover->choose_Moves[action].probability = move_probabilities[i].probability;
            break;
        }
    }

    // Afficher les nouvelles probabilités pour débogage
    printProbabilities(move_probabilities, NUM_MOV);
}
