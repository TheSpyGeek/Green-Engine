# Moteur de jeu
#### TP4 : Mouvements d’objets

par Maxime Isnel

lien du Git de [Green Engine](https://github.com/TheSpyGeek/Green-Engine) : https://github.com/TheSpyGeek/Green-Engine

## Compiler le code

##### Sur Linux

Dependencies :

```sudo apt-get install -y build-essential cmake xorg-dev libgl1-mesa-dev libfreetype6-dev```

Pour compiler :

```cd build && cmake .. && make```

##### Sur Windows

Dependencies :

* mingw64 ou mingw32
* cmake

Pour compiler :

* Lancer ```Cmake```
* Configurer avec les ```Mingw Makefile``` pour compiler dans le dossier ```build```
* Lancer ```mingw64```
* Aller dans le dossier ```build```
* Compiler avec ```mingw32-make```

Pour lancer le programme :

 ```./green-engine```

## Structure du code

Les grandes classes du programme sont :
* **MainRenderer** : il fait le rendu d'une scène dans une texture et puis l'affiche dans une texture
* **InputManager** : gère les entrées clavier et les associent avec des fonctions du moteur
* **UI** : gère tout l'affichage des widgets sur l'écran (hors rendu). Le méthode d'affichage de chaque composant d'un objet sont défini dans les objet eux mêmes
* **Scene** : gère tous les objets du moteur (ajout, suppression, mise à jour). Elle possède une liste d'**ObjectEngine**
* **ObjectEngine** : Est un objet géré par la scène. Il possède un **Transform** ce qui permet de le déplacer. Il possède une liste d'**ObjectEngine** qui sont ses fils et dont les positions et rotations vont dépendre de la matrice model du parent.
* **MeshObject** : Il possède un maillage donc ils sont affichable. Il possède un **Material** qui va faire le shading et la couleur de l'affichage de cette objet.
* **Player** : C'est un meshObject un peu spéciale. On peut le déplacer avec Z,Q,S,D. Il va rester à une certaine hauteur de terrain.

### Mouvements de l'objet

Pour faire en sorte que cet objet suivent le terrain à chaque frame je cherche ou il se trouve sur le terrain (sur quel triangle). Puis j'interpole la hauteur du triangle à la position x et z de l'objet pour avoir le y en ce point. Puis j'affecte ce y plus une constante à mon objet.

### Variation LOD

J'ai aussi crée 3 maillages pour l'objet Player qui sont trois maillages à des résolutions différentes (full, medium et low). Je choisis celui que j'affiche en fonction de la distance à la caméra. Pour vérifier cela, j'affiche dans la fenetre Debug en haut a gauche la distance entre la caméra et mon objet et le nombre de sommets et triangle dans le maillage courant. Si vous zoomez (molette de la souris), vous pouvez voir que ces nombres vont changer. Vous pouvez aussi faire l'affichage en WireFrame (CTRL+F) pour voir les différents maillages.


## Fonctionnalités

Vous pouvez :

 * Vous pouvez redimensionner la fenêtre de l'application et la fenêtre du **scene manager**
 * Ouvrir un arbe dans le **scene manager** si l'objet à des fils en clique sur la flèche
 * Ajouter des objets avec maillage en faisant ```Edit => Add MeshObject```. Vous pouvez ensuite changer le maillage chargé en changeant le chemin du fichier .OFF et en appuyant sur le bouton "Recreate"
 * Afficher l'objet avec des ```WireFrame``` en faisant ```View => Toggle wire frame```
 * Faire tourner les objets, les déplacer, ...
 * Avec ```CTRL + H``` vous pouvez cacher/montrer l'affichage des fenêtre.
