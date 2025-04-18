/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learn_iso.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:48:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/02/27 11:10:13 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Comprendre les bases de l'isométrie sans utiliser MiniLibX.
Déclare une structure pour représenter un point en 3D.
Projette ce point en 2D en utilisant une formule d'isométrie.
Affiche les résultats dans le terminal pour vérifier les calculs. */

/* Formule de Projection Isométrique :
Pour convertir un point 3D (x, y, z) en point 2D (x2d, y2d) :

x2d = (x - y) * cos(0.523599);
y2d = (x + y) * sin(0.523599) - z;

-> 0.523599 = 30° en radians (angle utilisé pour l'isométrie)
-> cos(30°) ≈ 0.866 et sin(30°) = 0.5
 */

#include <stdio.h>
#include <math.h>

#define ISO_ANGLE 0.523599  // 30° en radians

// Structure pour un point 3D en float
// (les div et multipli en int tronquent les valeurs)
typedef struct {
	float x;
	float y;
	float z;
} Point3D;

// Structure pour un point 2D
typedef struct {
	float x;
	float y;
} Point2D;

// Fonction de projection isométrique
Point2D iso_projection(Point3D p) {
	Point2D result;
	result.x = (p.x - p.y) * cos(ISO_ANGLE);
	result.y = (p.x + p.y) * sin(ISO_ANGLE) - p.z;
	return (result);
}

/*
result.x = (p.x - p.y) * cos(ISO_ANGLE);
- p.x - p.y : Cela décale le point sur l'axe horizontal.
	- Plus x est grand, plus le point va à droite.
	- Plus y est grand, plus le point va à gauche.
- cos(ISO_ANGLE) :
	- ISO_ANGLE = 0.523599 qui est 30° en radians.
	- cos(30°) ≈ 0.866.
	- On utilise le cosinus car il détermine l'effet de décalage horizontal.

result.y = (p.x + p.y) * sin(ISO_ANGLE) - p.z;
- (p.x + p.y) * sin(ISO_ANGLE) :
	- p.x + p.y : Combine les coordonnées pour donner une hauteur isométrique.
	- sin(30°) = 0.5 : Utilisé pour réduire cette hauteur.
	- Cela donne l'effet de profondeur sur l'axe vertical.
- p.z :
	- C'est ce qui crée l'effet de relief !
	- Plus le z est grand, plus le point monte sur l'écran (comme une montagne).

           z
           |
          (.)   <-- Le point en 3D
         / | \
        /  |  \
       /   |   \
      /    |    \
     /_____|_____\
    x              y
Le point est projeté sur un plan 2D en combinant les effets de x, y et z.
Le x et y définissent la position de base.
Le z élève ou abaisse le point sur l'écran.


En isométrie, on utilise des rotations pour donner une perspective 3D :
Le cosinus gère le décalage horizontal.
Le sinus gère la profondeur verticale.
Cela simule un angle de vue à 30° (isométrie).
En résumé :
On combine x et y pour obtenir une position isométrique.
On soustrait z pour donner un effet de hauteur (relief).

*/

int	main(void)
{
	// Déclaration des points en 3D
	Point3D points[4] = {
		{0, 0, 0},
		{1, 0, 1},
		{1, 1, 2},
		{0, 1, 3}
	};

	// Projection et affichage des résultats
	printf("Projection Isométrique :\n");
	int	i;
	i = 0;
	while (i < 4)
	{
		Point2D projected = iso_projection(points[i]);
		printf("3D (%.1f, %.1f, %.1f) -> 2D (%.1f, %.1f)\n",
			   points[i].x, points[i].y, points[i].z,
			   projected.x, projected.y);
		i++;
	}
	return (0);
}

/* Compilation et Exécution :
gcc main.c -o isometric -lm
./isometric

ici, -lm est nécessaire pour lier la bibliothèque mathématique (math.h).
 */


/* Explication du Code :
Structure Point3D et Point2D : Permet de manipuler facilement les coordonnées des points.
iso_projection() : Convertit un point 3D en 2D en utilisant la formule d'isométrie.
main() :
	- Initialise 4 points en 3D pour tester la projection.
	- Affiche les résultats des projections dans le terminal. */


/* L'isométrie donne un effet 3D en représentant les trois dimensions (x, y, z)
sur un plan 2D (x, y).
On simule la profondeur sans perspective : les dimensions sont proportionnelles
et les angles sont de 120°. */


/* Expérimenter :
Modifie l'angle : Change ISO_ANGLE pour voir comment ça change la projection.
Ajoute plus de points pour mieux visualiser la grille.
Affiche les valeurs intermédiaires avec printf() pour bien suivre les calculs. */
