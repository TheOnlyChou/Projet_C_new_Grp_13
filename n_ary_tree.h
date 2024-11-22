//
// Created by TheOnlyChou
//
#ifndef N_ARY_TREE_H
#define N_ARY_TREE_H

#include "prob_mov.h" // Récupération de la structure t_move_probability (mouvements possibles)
#include "map.h" // Récupération de la structure t_soil (type de sol)

/**
 * @brief Structure : noeud de l'arbre
 */
typedef struct s_node
{
    t_move_probability move_probability; // Mouvements possibles en fonction des probabilités pour le noeud
    t_soil TypeSoil; // Type de sol pour le coût du mouvement et les aléas
    int cost_move; // Coût du mouvement dépendant du type de sol
    struct s_node *children[9]; // Tableau des enfants (max 9)
    struct s_node *parent; // Parent du noeud pour le backtracking (parcours en largeur)
    int numChildren;
} t_node;

/**
 * @brief Structure : arbre
 */
typedef struct s_tree
{
    t_node *root;
} t_tree;

/**
 * @brief Fonction pour créer un noeud
 * @param move_p : le mouvement et sa probabilité
 * @param TypeSoil : le type de sol
 * @param cost_move : le coût du mouvement
 * @return le noeud créé
 */
t_node *createNode(t_move_probability move_p, t_soil TypeSoil, int cost_move);

/**
 * @brief Fonction pour ajouter un enfant à un parent
 * @param parent : le parent
 * @param child : l'enfant
 */
void addChild(t_node *parent, t_node *child);

/**
 * @brief Fonction pour créer un arbre vide
 * @return l'arbre créé
 */
t_tree createEmptyTree();

/**
 * @brief Fonction pour libérer la mémoire de l'arbre
 * @param node : le noeud à libérer
 */
void freeTree(t_node *node);

/**
 * @brief Fonction pour afficher l'arbre n-aire
 * @param node : le noeud à afficher
 */
void displayNaryTree(t_node *node);


#endif //N_ARY_TREE_H
