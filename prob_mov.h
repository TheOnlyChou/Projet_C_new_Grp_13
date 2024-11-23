#ifndef PROB_MOV_H
#define PROB_MOV_H

#include "moves.h"

#define NUM_MOV 7 // Nombre de mouvements possibles
#define SEL_MOV 5 // Nombre de mouvements sélectionnés

/**
 * @brief Structure : mouvement et probabilité
 */
typedef struct
{
    t_move move;
    float probability;
} t_move_probability;

/**
 * @brief Tableau des mouvements et des probabilités (7 mouvements 2 qui se répètent => 9 mouvements)
 * fonctionne comme un dictionnaire en Python
 */
// Conversion de double en float pour éviter les warnings
static t_move_probability move_probabilities[NUM_MOV] =
        {
                {F_10, 22.0f}, //[0]
                {F_20, 15.0f}, //[1]
                {F_30, 7.0f}, //...
                {B_10, 7.0f},
                {T_LEFT, 21.0f},
                {T_RIGHT, 21.0f},
                {U_TURN, 7.0f} //[6]
        };

/**
 * @brief Fonction pour réinitialiser les probabilités de base
 */
void resetProbabilities();

/**
 * @brief Fonction pour mélanger les probabilités (proposition de Halim Djerroud)
 * https://www.youtube.com/watch?v=GS2MxmorEzc
 * @param array : tableau des probabilités
 * @param n : nombre de mouvements
 */
void shuffle(t_move_probability *array, int n);

/**
 * @brief Fonction pour sélectionner un mouvement en ajoutant le bug qui enlève 1% de chance à chaque mouvement
 * @return le mouvement sélectionné
 */
t_move selectMove();

void chooseNineMoves(t_move selected_moves[9]);
/**
 * @brief Fonction pour choisir 9 mouvements parmie les 7 possibles (2 qui se répètent)
 * @param selected_moves : tableau des mouvements sélectionnés (9)
 */

/**
 * @brief Fonction pour choisir les mouvements à effectuer
 * @param selected_moves : tableau des mouvements sélectionnés
 */
void chooseMoves(t_move selected_moves[SEL_MOV]);

/**
 * @brief Fonction pour afficher les probabilités des mouvements
 * @param probabilities : pointeur sur un tableau des probabilités
 * @param size : taille du tableau
 */
void printProbabilities(t_move_probability *probabilities, int size);


#endif //PROB_MOV_H