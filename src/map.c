/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:40:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 16:08:40 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
	Gérer la lecture, le stockage et la libération de la map :

	Alloc mémoire pour la grille de points (alloc_grid)
	- Alloue un tableau 2D de `t_point` pour représenter la carte.
	- Si une allocation échoue, libère tout proprement avec free_grid().

	Free mémoire de la grille (free_grid)
	- Libère chaque ligne de la grille et enfin la grille elle-même.

	Lecture et découpage couleur/token de la carte (parse_token)
	- Lit une valeur de hauteur (z) et éventuellement une couleur (hexadécimale).
	- Associe les coordonnées `(x, y)` et la couleur à chaque `t_point`.

	Lecture et découpage d'une ligne complète de la carte (parse_line)
	- Lit tous les "tokens" d'une ligne (séparés par des espaces).
	- Pour chaque token, appelle `parse_token`.

	Lecture complète de la carte depuis un fichier (parse_map)
	- Ouvre et lit le fichier ligne par ligne.
	- Calcule la largeur et la hauteur de la carte.
	- Alloue la grille de points.
	- Remplit la grille avec les valeurs lues.
*/

static t_point	**alloc_grid(int width, int height)
{
	t_point	**grid;
	int		i;

	grid = ft_calloc(height + 1, sizeof(t_point *));
	if (!grid)
	{
		error_message("[ALLOC ERROR]: grid malloc failed\n", 1);
	}
	i = -1;
	while (++i < height)
	{
		grid[i] = malloc(sizeof(t_point) * width);
		if (!grid[i])
		{
			error_message("[ALLOC ERROR]: row malloc failed\n", 1);
			free_grid(grid);
		}
	}
	return (grid);
}

void	free_grid(t_point	**grid)
{
	int	i;

	if (grid)
	{
		i = 0;
		while (grid[i])
		{
			free(grid[i]);
			i++;
		}
		free(grid);
	}
}

void	parse_map(char *filename, t_map *map)
{
	get_map_size(filename, map);
	map->grid = alloc_grid(map->width, map->height);
	fill_grid(filename, map);
}
