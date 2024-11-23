#include <stdio.h>
#include <stdlib.h>

#include "n_ary_tree.h"

t_node *createNode(t_move_probability move_p, t_soil TypeSoil, int cost_move)
{
    t_node *node = (t_node *)malloc(sizeof(t_node));
    node->move_probability = move_p;
    node->TypeSoil = TypeSoil;
    node->cost_move = cost_move;
    node->numChildren = 0;
    node->parent = NULL;
    return node;
}

void addChild(t_node *parent, t_node *child)
{
    parent->children[parent->numChildren++] = child;
}

t_tree createEmptyTree()
{
    t_tree tree;
    tree.root = NULL;
    return tree;
}

void freeTree(t_node *node)
{
    if (node == NULL)
    {
        return;
    }
    for (int i = 0; i < node->numChildren; i++)
    {
        freeTree(node->children[i]);
    }
    free(node);
}

void displayNaryTree(t_node *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("Noeud : Move = %d, Probability = %f\n", node->move_probability.move, node->move_probability.probability);
    printf("Type de sol : %d\n", node->TypeSoil);
    printf("Coût du mouvement : %d\n", node->cost_move);
    printf("Nombre d'enfants : %d\n", node->numChildren);
    for (int i = 0; i < node->numChildren; i++)
    {
        displayNaryTree(node->children[i]);
    }
}
