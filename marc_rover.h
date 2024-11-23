//
// Created by alex8 on 22/11/2024.
//

#ifndef MARC_ROVER_H
#define MARC_ROVER_H

#include "loc.h" // Pour récupérer la structure t_localisation pour le robot MARC
#include "prob_mov.h" // Pour récupérer la structure t_move pour les mouvements aléatoires
#include "n_ary_tree.h" // Pour récupérer la structure t_tree pour l'arbre n-aire
#include "stack.h" // Pour récupérer la structure t_stack pour la pile

/**
 * @brief Structure pour le robot MARC
 */
typedef struct s_marc_rover
{
    t_localisation  loc;
    int total_cost;
    t_move_probability choose_Moves[SEL_MOV];
    t_tree tree;
} t_marc_rover;

/**
 * @brief Fonction pour créer un robot MARC
 * @param loc : la localisation du robot MARC
 * @param total_cost : le coût total du parcours
 * @param tree : l'arbre n-aire du robot
 * @return le robot créé
 */
t_marc_rover createMarcRover(t_localisation loc, int total_cost, t_tree tree);

/**
 * @brief : Fonction pour libérer la mémoire
 * @param marc_rover : le robot MARC à libérer
 */
void freeMarcRover(t_marc_rover *marc_rover);

/*
 * @brief Fonction pour afficher le robot MARC
 * @param marc_rover : le robot MARC à afficher
 */
void displayMarcRover(t_marc_rover marc_rover);

/**
 * @brief Fonction pour diminuer les actions possibles du robot MARC
 * @param marc_rover : le robot MARC
 * @param action : l'action à diminuer
 */
void decreaseActions(t_marc_rover *marc_rover, int action);

/**
 * @brief Fonction pour créer l'arbre n-aire du robot MARC
 * @param map : la carte
 * @param tree : l'arbre n-aire
 * @param rover : le robot MARC
 */
void createTree(t_map *map, t_tree *tree, t_marc_rover *rover);

/**
 * @brief Fonction pour trouver la feuille avec le coût minimal
 * @param tree : l'arbre n-aire
 * @return la feuille avec le coût minimal
 */
t_node *findMinLeaf(t_tree *tree);

#endif //MARC_ROVER_H
