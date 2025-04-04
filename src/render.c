/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:40:03 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 15:56:07 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
	Affichage de la carte complète (rendering) :

	Effacer l'ancienne image :
	- Nettoyer la fenêtre existante (`mlx_clear_window`).
	- Réinitialiser complètement le buffer d'image avec `ft_bzero`
	  (mettre tous les pixels à 0, c'est-à-dire noir).

	Redessiner toute la map :
	- Parcours **ligne par ligne** (`y`) puis **point par point** (`x`).
	- À chaque point, dessiner les connexions vers la droite et vers le bas
	(`draw_connections`).

	Envoyer l'image à l'écran :
	- Une fois toute l'image recréée dans le buffer, afficher l'image sur la fenêtre
	avec `mlx_put_image_to_window`.
*/

void	render_map(t_engine *engine)
{
	int	x;
	int	y;

	mlx_clear_window(engine->mlx, engine->window);
	ft_bzero(engine->image.addr_ptr, WIN_WIDTH * WIN_HEIGHT * 4);
	y = 0;
	while (y < engine->map.height)
	{
		x = 0;
		while (x < engine->map.width)
		{
			draw_connections(engine, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(engine->mlx, engine->window,
		engine->image.img_ptr, 0, 0);
}
