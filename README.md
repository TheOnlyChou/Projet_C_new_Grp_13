# Rover run ! READ ME

## Lien de dépot github : https://github.com/nicolas-flasque-efrei/MARC

## Lien de la prise de notes : https://docs.google.com/document/d/1TVoH-4Attqpg8qIkM9Ik9TOuN9myZSAibGMzAoftveY/edit?tab=t.0

Fichier prob_mov.h et prob_mov.c :

Initialiser les Probabilités:

Une structure est définie pour stocker les mouvements et leurs probabilités initiales.

Reset des Probabilités:

Les probabilités sont réinitialisées au début de chaque phase pour garantir un nouveau départ.

Random Shuffle:

Les mouvements sont mélangés pour assurer un tirage aléatoire, permettant une distribution équitable des choix.

Diminuer les Probabilités:

Chaque fois qu'un mouvement est choisi, sa probabilité est réduite de 1% et il est replacé dans la pile pour un usage futur.

Choisir les Mouvements:

Les mouvements sont sélectionnés en fonction des probabilités ajustées, favorisant ceux qui n'ont pas été choisis récemment.

Fichier n_ary_tree.h et n_ary_tree.c (Partie 1 => Arbre N-aire simple):

Définition de la structure de l'arbre N-aire : chaque nœud représentera une position sur la carte avec des informations associées.

Fonctions de création et de gestion de l'arbre : création de nœuds, ajout d'enfants, etc.

Construction d'un arbre simple : génération d'un arbre avec des choix de mouvements.