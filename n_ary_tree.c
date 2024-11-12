#include <stdio.h>
#include <stdlib.h>

#include "n_ary_tree.h"

t_node *createNode(t_position pos, int cost, t_soil soilType, t_node *parent,int maxChildren)
{
    t_node *node = malloc(sizeof(t_node));

    node->pos = pos;
    node->cost = cost;
    node->soilType = soilType;
    node->parent = parent;
    node->numChildren = 0;

    node->children = malloc(maxChildren * sizeof(t_node*));

    if(parent != NULL)
    {
        node->totalCost = parent->totalCost + cost;
    }
    else
    {
        node->totalCost = cost;
    }

    return node;
}

void addChild(t_node *parent, t_node *child)
{
    parent->children[parent->numChildren++] = child;
}

void build_simple_tree(t_nary_tree* tree)
{
    t_position root_pos;
    root_pos.x = 0;
    root_pos.y = 0;
    tree->root = createNode(root_pos, 0, PLAIN, NULL, 2);

    t_position child1_pos;
    child1_pos.x = 0;
    child1_pos.y = 1;
    t_node* child1 = createNode(child1_pos, 5, ERG, tree->root, 0);

    t_position child2_pos;
    child2_pos.x = 1;
    child2_pos.y = 0;
    t_node* child2 = createNode(child2_pos, 8, PLAIN, tree->root, 0);

    tree->root->children[tree->root->numChildren++] = child1;
    tree->root->children[tree->root->numChildren++] = child2;
}

