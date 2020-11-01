Fichier descriptif du projet MiniGames


------------
Concept
------------
Le but du jeu est de trouver la différence entre les deux "images".
On verra à l'écran deux images : l'originale et la copie.
Le but du jeu est de trouver ce qui montre que la copie est "Fausse"

------------
Règles
------------
Il faut identifier la "créature" de droite qui est différente de celle qui lui correspond dans le tableau original (à gauche)
Une fois identifiée, il faut cliquer (clic gauche) sur la différence.

------------
Comment compiler et lancer le programme ?
------------
En utilisant des commandes dans un terminal :
Il faut entrer la commande suivante (uniquement pour la première éxécution) :
	./compile.sh
Puis (Pour chaque lancement du jeu) :
	./a.out

------------
Description des fichiers écrits
------------
Comme cela doit se remarquer sur la qualité (et dans le code), j'ai préféré utilisé la bibliothèque SDL et partir de zéro.
Néanmoins, une partie de la structure d'affichage (notamment l'initialisation, une partie basique de la boucle principale et la libération de la mémoire) est copié.
La structure simple du jeu le permettant, la totalité du code est situé dans le main.

J'ai codé ce jeu par itération, en réalisant un commit pour chaque version stable :
- Le premier affichage d'image
- Affichage de plusieurs images aux positions choisies
- Affichage de ce qui pourrait être une image du jeu
- Gestion de l'enregistrement du clic (et des actions qui s'ensuivent)
- Ajout de l'aléatoire, pour rendre ce puzzle game toujours intéressant.
- Ajout de nombreuses images pour pouvoir faire des difficultés.
- [PAS DE COMMIT] Tentatives de réalisation d'un menu pour choisir une difficulté
- Ajout d'une fin lors de la réussite du puzzle
- Ajout de l'enregistrement du temps d'une partie 
- [PAS DE COMMIT] Tentatives de réalisation d'un menu, dans lequel s'affiche le meilleur temps

------------
Améliorations possibles :
------------
Déjà envisagées (mais échecs) :
- Création d'un menu
- Choix d'une difficultée
- Ajout d'un top score

Autres (simples idées, pas abordées) :
- Ajout d'une musique pour accompagner le jeu
- Utilisation d'une suite d'image par créature pour ajouter du mouvement (comme un gif ?)
- Centrer la fenêtre au lancement (maintenant que j'y pense, c'est sans doute une des premières choses que j'aurais du regardé ...)

------------
Bibliothèques utilisées
------------
Installées pour coder avec la SDL :
libsdl-image1.2
libsdl1.2-dev

Appelées dans le main:
stdio.h
SDL/SDL.h
stdbool.h
SDL/SDL_image.h
stdlib.h
time.h

------------
Crédits images
------------
https://opengameart.org/content/32x32-pixel-art-creatures-volume-3
