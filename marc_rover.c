//
// Created by alex8 on 22/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "marc_rover.h"
#include "moves.h"

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

void createTree(t_map *map, t_tree *tree, t_marc_rover *rover)
{
    // Initialisation de la racine de l'arbre avec la position actuelle du rover
    t_node *root = createNode(
            rover->choose_Moves[0],
            map->soils[rover->loc.pos.y][rover->loc.pos.x],
            map->costs[rover->loc.pos.y][rover->loc.pos.x]
    );
    tree->root = root;

    // Création d'une pile pour gérer les nœuds à traiter
    t_stack stack = createStack(100);
    push(&stack, root);

    while (stack.nbElts > 0)
    {
        t_node *current_node = (t_node *)pop(&stack);

        // Vérification de la profondeur pour limiter à 5 mouvements
        int current_depth = 0;
        t_node *temp = current_node;
        while (temp != NULL)
        {
            current_depth++;
            temp = temp->parent;
        }
        if (current_depth >= 5)
        {
            continue;
        }

        // Nombre de mouvements disponibles, ajusté pour le terrain REG
        int num_moves = SEL_MOV;

        // Parcours des mouvements possibles
        for (int i = 0; i < num_moves; i++)
        {
            t_localisation new_pos = move(rover->loc, rover->choose_Moves[i].move);

            // Vérification de validité de la nouvelle position
            if (isValidLocalisation(new_pos.pos, map->x_max, map->y_max))
            {
                t_soil soil = map->soils[new_pos.pos.y][new_pos.pos.x];
                int new_cost = map->costs[new_pos.pos.y][new_pos.pos.x] + _soil_cost[soil];

                // Gestion des terrains spéciaux
                if (soil == ERG)
                {
                    // Terrain ERG : Réduction de l'efficacité des mouvements (ajuster le coût)
                    if (rover->choose_Moves[i].move == F_10 || rover->choose_Moves[i].move == B_10)
                    {
                        new_cost += 1; // Mouvement inefficace sur ERG
                    }
                    else if (rover->choose_Moves[i].move == F_20)
                    {
                        new_cost += 2;
                    }
                    else if (rover->choose_Moves[i].move == F_30)
                    {
                        new_cost += 3;
                    }
                }
                else if (soil == REG)
                {
                    // Terrain REG : Limiter les mouvements à 4 pour la phase suivante
                    num_moves = SEL_MOV - 1; // Réduire le nombre de mouvements disponibles
                }
                else if (soil == CREVASSE)
                {
                    new_cost = COST_UNDEF; // Crévasse : mouvement impossible
                }

                // Création du nœud enfant
                t_node *child = createNode(rover->choose_Moves[i], soil, new_cost);
                child->parent = current_node;
                addChild(current_node, child);

                // Arrêt précoce si la station de base est atteinte
                if (new_cost == 0)
                {
                    return;
                }

                // Ajout de l'enfant dans la pile pour exploration
                if (new_cost < COST_UNDEF)
                {
                    push(&stack, child);
                }
            }
        }
    }
}

t_node *findMinLeaf(t_tree *tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        return NULL; // Aucun nœud dans l'arbre
    }

    t_node *min_leaf = NULL;
    int min_cost = INT_MAX;

    // Création d'une pile pour parcourir l'arbre en largeur
    t_stack stack = createStack(100);
    push(&stack, tree->root);

    while (stack.nbElts > 0)
    {
        t_node *current = (t_node *)pop(&stack);

        // Vérification si le nœud est une feuille
        if (current->numChildren == 0)
        {
            if (current->cost_move < min_cost)
            {
                min_cost = current->cost_move;
                min_leaf = current;
            }
        }

        // Ajouter les enfants à la pile pour exploration
        for (int i = 0; i < current->numChildren; i++)
        {
            push(&stack, current->children[i]);
        }
    }

    // Libération de la mémoire de la pile
    free(stack.values);

    return min_leaf;
}

t_localisation applyMove(t_localisation loc, t_move move)
{
    t_localisation new_loc = loc;
    switch (move)
    {
        case F_10:
            if (loc.ori == NORTH) new_loc.pos.y -= 1;
            else if (loc.ori == SOUTH) new_loc.pos.y += 1;
            else if (loc.ori == EAST) new_loc.pos.x += 1;
            else if (loc.ori == WEST) new_loc.pos.x -= 1;
            break;
        case F_20:
            if (loc.ori == NORTH) new_loc.pos.y -= 2;
            else if (loc.ori == SOUTH) new_loc.pos.y += 2;
            else if (loc.ori == EAST) new_loc.pos.x += 2;
            else if (loc.ori == WEST) new_loc.pos.x -= 2;
            break;
        case T_LEFT:
            new_loc.ori = (loc.ori + 3) % 4;
            break;
        case T_RIGHT:
            new_loc.ori = (loc.ori + 1) % 4;
            break;
        case U_TURN:
            new_loc.ori = (loc.ori + 2) % 4;
            break;
        default:
            printf("Mouvement inconnu : %d\n", move);
            break;
    }
    return new_loc;
}

void renderMap(t_map* map, t_position roverPosition)
{
    for (int i = 0; i < map->y_max; i++)
    {
        for (int rep = 0; rep < 3; rep++)
        {
            for (int j = 0; j < map->x_max; j++)
            {
                char c[4];
                if (i == roverPosition.y && j == roverPosition.x)
                {
                    strcpy(c, " R ");
                } else
                {
                    switch (map->soils[i][j])
                    {
                        case 0: strcpy(c, " B "); break;
                        case 1: strcpy(c, "---"); break;
                        case 2: strcpy(c, "~~~"); break;
                        case 3: strcpy(c, "^^^"); break;
                        case 4: sprintf(c, "%c%c%c", 219, 219, 219); break;
                        default: strcpy(c, "???"); break;
                    }
                }
                printf("%s", c);
            }
            printf("\n");
        }
    }
}

int* generatePath(t_node* target, int* pathLength, int* totalCost)
{
    if (!target)
    {
        printf("Erreur : noeud cible invalide.\n");
        return NULL;
    }

    t_node* current = target;
    int steps = 0;

    while (current->parent)
    {
        steps++;
        current = current->parent;
    }

    int* path = malloc(steps * sizeof(int));
    if (!path)
    {
        printf("Erreur : allocation mémoire échouée.\n");
        return NULL;
    }

    current = target;
    *totalCost = 0;
    for (int i = steps - 1; i >= 0; i--)
    {
        path[i] = current->move_probability.move;
        *totalCost += current->cost_move;
        current = current->parent;
    }

    *pathLength = steps;
    return path;
}

void directRover(t_marc_rover* rover, const int* path, int pathLength)
{
    printf("Debut de la navigation. Position initiale : (%d, %d)\n",rover->loc.pos.x, rover->loc.pos.y);

    for (int step = 0; step < pathLength; step++)
    {
        t_move move = (t_move)path[step];
        rover->loc = applyMove(rover->loc, move);

        printf("Etape %d : Position actuelle : (%d, %d), Orientation : %d\n",step + 1, rover->loc.pos.x, rover->loc.pos.y, rover->loc.ori);
    }

    printf("Navigation terminee. Position finale : (%d, %d)\n",rover->loc.pos.x, rover->loc.pos.y);
}

void followPath(t_map* map, t_marc_rover* rover, const int* path, int pathLength)
{
    printf("Position initiale du rover :\n");
    renderMap(map, rover->loc.pos);
    printf("\n");

    for (int step = 0; step < pathLength; step++)
    {
        t_move move = (t_move)path[step];
        rover->loc = applyMove(rover->loc, move);

        printf("Etape %d :\n", step + 1);
        renderMap(map, rover->loc.pos);
        printf("\n");
    }

    printf("Position finale atteinte : (%d, %d)\n", rover->loc.pos.x, rover->loc.pos.y);
}


