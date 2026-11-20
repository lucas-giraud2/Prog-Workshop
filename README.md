# Prog Workshop
## *<ins>♦ Ex 1 : Ne garder que le vert</ins>*
Passage des canaux rouge et bleu à 0. (pas besoin des x et y)

![image](./output/green_only.png)

## *<ins>♦ Ex 2 : Échanger les canaux</ins>*
Utilisation de std::swap(color.g, color.b) pour échanger les canaux vert et bleu.
Sinon manuellement on doit mémoriser les composantes de chaque pixel avant de faire une modification pour ne pas perdre l'information.

![image](./output/echange_canaux.png)

## *<ins>♦ Ex 3 : Noir & Blanc</ins>*
Il faut que tous les canaux soit égaux. La formule du gris est gris = 0.2126 * r + 0.7152 * g + 0.0722 * b

![image](./output/gris.png)

## *<ins>♦ Ex 4 : Négatif</ins>*
Création d'une base {1, 1, 1} pour ne représenter que le blanc (le max), puis on calcule la différence entre ce blanc et la couleur du pixel pour inverser la couleur.

![image](./output/negatif.png)

## *<ins>♦ Ex 5 : Dégradé</ins>*
La nuance de gris va dépendre de x (la longueur). On parcours toute l'image en mettant chaque pixel avec les trois même canaux dépendant de x et de la longueur de l'image.

![image](./output/degrade.png)

## *<ins>♦ Ex 6 : Miroir</ins>*
Parcours de la moitié de l'image en x (dans la longueur) et on utilise std::swap() pour interchanger le symétrique du pixel par rapport à la verticale qui passe au centre d l'image.

![image](./output/miroir.png)

## *<ins>♦ Ex 7 : Image bruitée</ins>*
Utilisation des fonctions random fournies, ici true_with_probability et random_float pour choisir aléatoirement un pixel est changer ses couleurs de façon aussi aléatoire.

![image](./output/bruit.png)

## *<ins>♦ Ex 8 : Rotation de 90°</ins>*
Mathématiquement, les axes sont interchangés lors d'une rotation à 90°. Ici x devient y et y devient -x. On change donc les pixels en créant une nouvelle image noir qui à pour dimension en x en y et les y en x et en faisant attention à rester dans l'image au moment de remplir la nouvelle image.

![image](./output/negatif.png)

## *<ins>♦ Ex 9 : RGB Split</ins>*
On crée une nouvelle image dans laquelle on va recopier les différents canaux de couleurs en ajoutant des contraintes.
Je fais un décalage de 15 pixels vers la droite pour le canal rouge et 15 vers la gauche pour le canal bleu. On doit mettre une condition de marge pour ne pas dépasser, qui sera donc ici de 15 pixels.

![image](./output/rgb_split.png)

## *<ins>♦ Ex 10 : Luminosité</ins>*
- J'utilise la fonction carré pour assombrir l'image, en multipliant les canaux de chaque pixel par eux-mêmes.

![image](./output/luminosite_assombrir.png)

- J'utilise la fonction std::pow() de la librairie cmath pour éclairer l'image. Il suffit de choisir un flottant inférieur à 1 pour avoir cet effet, ici 0.4f.

![image](./output/luminosite_eclaircir.png)

## *<ins>♦ Ex 11 : Disque</ins>*
Grace à l'équation d'un cercle adapté au centre de l'image n'étant pas l'origine, on peut mettre une condition sur le changement des pixels.
1 étant la valeur la plus forte de lumière.

![image](./output/disque.png)

## *<ins>♦ Ex 12 : Cercle</ins>*
Le cercle fonctionne exactement de la même façon que le disque, on doit simplement rajouter une condition qui évolue en fonction de la thickness, pour créer un rebord. (l'intérieur de tout le disque n'est plus en blanc)

![image](./output/cercle.png)

## *<ins>♦ Ex 13 : Animation</ins>*
J'ai adapté la fonction disque avec des paramètres pour pouvoir la réutiliser. Il ne reste plus qu'à se déplacer de quelques pixels et refaire un disque à chaque fois en sauvegardant bien chaque image et en recréant une nouvelle image à chaque itération sinon on garde les disques précédents.
Puis il ne reste plus qu'à transformer les images en animation.

![image](./output/animation/anim.gif)

## *<ins>♦ Ex 14 : Rosace</ins>*
J'ai adapté la fonction cercle avec des paramètres pour pouvoir la réutiliser. J'ai voulu gérer le nombre de pétales donc je boucle sur ce dernier. Le calcul de l'angle se fait en radiant en divisant une tour complet c'est à dire 2*Pi par le nombre de pétales et l'angle augmentera au fil des itérations.
<ins>*Remarque*</ins> : std::cos et std::sin qui donne les coordonnées d'un point sur un cercle unitaire.

![image](./output/rosace.png)

## *<ins>♦ Ex 15 : Mosaïque</ins>*
On a besoin de se servir du module (reste de la division euclidienne) pour adapter le parcours de la nouvelle image plus grande.

![image](./output/mosaique.png)

## *<ins>♦ Ex 16 : Mosaïque miroir</ins>*
On a besoin de savoir en fonction de la taille de l'image de base si on est sur une colonne paire pour recopier comme dans mosaïque. Sinon on recopie à l'envers.

- On peut faire un effet un peu rétro

## *<ins>♦ Ex 17 : Glitch</ins>*
Probabilité très faible sinon l'image est trop susceptible de changer à chaque pixel et les modifications de se marcher dessus.
Je récupère les longueur et largeur aléatoirement pour faire un rectangle dont je récupère les pixels que j'échange avec les pixels d'un autre rectangle choisi aussi au hasard dans toute l'image avec une marge du rectangle à échanger. Ce qui impose une condition sur où en est le parcours complet de l'image et la taille du rectangle choisie.
Après j'utilise swap pour changer depuis le pixel actuel jusqu'au pixel actuel + la taille de mon rectangle.

## *<ins>♦ Ex 18 : Tri de pixels</ins>*
Je crée une nouvelle image dans laquelle je vais recopier le tableau des pixels de l'image que je veux trier en récupérant d'abord les lignes puis les colonnes (on pourrait inverser le procédé pour obtenir un autre résultat). Puis on peut trier le tableau selon la condition que l'on veut, j'ai choisi ici le bleu.
Enfin je recopie le tableau ligne par ligne (on pourrait interchanger ici aussi ou choisir la façon dont on va disposer les pixels en introduisant une formule selon x, y, la longueur ou la largeur).