# Rover run ! READ ME

## Lien de dépot github : https://github.com/nicolas-flasque-efrei/MARC

## Lien de la prise de notes : https://docs.google.com/document/d/1TVoH-4Attqpg8qIkM9Ik9TOuN9myZSAibGMzAoftveY/edit?tab=t.0

Fichier prob_mov.h

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
