#include <stdio.h>
#include <stdlib.h>

#include "prob_mov.h"

void resetProbabilities()
{
    move_probabilities[0].probability = 22.0f;
    move_probabilities[1].probability = 15.0f;
    move_probabilities[2].probability = 7.0f;
    move_probabilities[3].probability = 7.0f;
    move_probabilities[4].probability = 21.0f;
    move_probabilities[5].probability = 21.0f;
    move_probabilities[6].probability = 7.0f;
}

void shuffle(t_move_probability *array, int n)
{
    if (n > 1)
    {
        for (int i = 0; i < n; i++)
        {
            int j = rand() % (i + 1);
            t_move_probability temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

t_move selectMove()
{
    shuffle(move_probabilities, NUM_MOV);
    for (int i = 0; i < NUM_MOV; i++)
    {
        if (move_probabilities[i].probability > 0)
        {
            move_probabilities[i].probability *= 0.99f; //Conversion de double en float pour éviter les warnings
            return move_probabilities[i].move;
        }
    }
    return (t_move)-1;
}

void chooseNineMoves(t_move selected_moves[9])
{
    resetProbabilities();
    for (int i = 0; i < 9; i++)
    {
        selected_moves[i] = selectMove();
    }
}

void chooseMoves(t_move selected_moves[SEL_MOV])
{
    t_move nine_moves[9];
    chooseNineMoves(nine_moves);
    for (int i = 0; i < SEL_MOV; i++)
    {
        selected_moves[i] = nine_moves[i % 9];
    }
}

void printProbabilities(t_move_probability *probabilities, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Mouvement %d: Probabilité = %f\n", i, probabilities[i].probability);
    }
}
