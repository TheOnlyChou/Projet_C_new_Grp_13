//
// Created by TheOnlyChou
//

#ifndef N_ARY_TREE_H
#define N_ARY_TREE_H

#include "loc.h" // Récupération de la structure t_position (x, y)
#include "map.h" // Récupération de la structure t_soil (type de sol)

/**
 * @brief Structure pour un noeud d'un arbre n-aire qui se base sur t_position et t_soil
 */
typedef struct t_node
{
    t_position pos;          // Position de MARC sur la carte (x, y)
    int cost;                // Coût associé au mouvement vers cette case (dépend du type de sol)
    int totalCost;           // Coût accumulé jusqu'à ce nœud (utile pour le backtracking) <=> trouver le chemin le moins coûteux
    t_soil soilType;         // Type de sol (erg, plaine, reg, etc.)

    struct t_node* parent;     // Pointeur vers le parent (utile pour retracer/comparer le chemin <=> backtracking) <=> récupérer la séquence de mouvements
    struct t_node** children;  // Pointeur vers les enfants (les mouvements possibles)
    int numChildren;         // Nombre d'enfants pour ce nœud
} t_node;

/**
 * @brief Structure de contrôle pour un arbre n-aire
 */
typedef struct s_nary_tree
{
    t_node* root;          // Position de départ (Base Station) de l'arbre
} t_nary_tree;

/*
 * @brief Initialise un noeud pour un arbre n-aire
 * @param pos : la position du noeud (x,y)
 * @param cost : le coût du mouvement vers ce noeud en fonction du type de sol
 * @param soilType : le type de sol de la case
 * @param parent : le parent du noeud
 * @param maxChildren : le nombre maximum d'enfants possibles pour ce noeud
 */
t_node *createNode(t_position pos, int cost, t_soil soilType, t_node *parent,int maxChildren);

/*
 * @brief Ajoute un enfant à un parent
 * @param parent : le parent
 * @param child : l'enfant à ajouter
 */
void addChild(t_node *parent, t_node *child);

/*
 * @brief Construit un arbre simple pour tester
 * @param tree : l'arbre à construire
 */
void build_simple_tree(t_nary_tree* tree);


#endif //N_ARY_TREE_H
