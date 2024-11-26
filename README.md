# Rover run ! READ ME

## Lien de dépot github : https://github.com/nicolas-flasque-efrei/MARC

## Lien de la prise de notes : https://docs.google.com/document/d/1TVoH-4Attqpg8qIkM9Ik9TOuN9myZSAibGMzAoftveY/edit?tab=t.0

Fichier prob_mov.h et prob_mov.c :
Initialiser les Probabilités :
Une structure est définie pour stocker les mouvements et leurs probabilités initiales.

Reset des Probabilités :
Les probabilités sont réinitialisées au début de chaque phase pour garantir un nouveau départ.

Random Shuffle :
Les mouvements sont mélangés pour assurer un tirage aléatoire, permettant une distribution équitable des choix.

Diminuer les Probabilités :
Chaque fois qu'un mouvement est choisi, sa probabilité est réduite de 1% et il est replacé dans la pile pour un usage futur.

Choisir les Mouvements :
Les mouvements sont sélectionnés en fonction des probabilités ajustées, favorisant ceux qui n'ont pas été choisis récemment.

Fichier n_ary_tree.h et n_ary_tree.c :
Définition de la structure de l'arbre N-aire :
Chaque nœud représentera une position sur la carte avec des informations associées.

Fonctions de création et de gestion de l'arbre :
Création de nœuds, ajout d'enfants, etc.

Construction d'un arbre simple :
Génération d'un arbre avec des choix de mouvements.

Fichier marc_rover.h et marc_rover.c :
Structure du robot MARC :
La structure t_marc_rover inclut la localisation, le coût total, les mouvements choisis et l'arbre n-aire.

Fonction createMarcRover :
Crée un robot MARC en initialisant la localisation, le coût total, les mouvements aléatoires parmi 9 et l'arbre n-aire.

Fonction freeMarcRover :
Libère la mémoire allouée pour le robot MARC.

Fonction displayMarcRover :
Affiche les informations du robot MARC, y compris la localisation, le coût total, les mouvements choisis et l'arbre n-aire.

Fonction decreaseActions :
Diminue les actions possibles du robot MARC, en sélectionnant un nouveau mouvement aléatoire lorsque nécessaire.

Fonction findMinLeaf :
Trouve le nœud feuille avec le coût minimal dans l'arbre.

Fonction generatePath :
Génère un chemin à partir du nœud feuille trouvé, renvoyant la longueur du chemin et le coût total.

Fonction renderMap :
Affiche la carte avec la position actuelle du rover.

Fonction directRover :
Dirige le rover tout en évitant le chemin généré.

Fonction followPath :
Fait suivre le chemin généré par le rover.

Fonction free :
Libère la mémoire allouée pour le chemin.
