/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:05:24 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 12:14:45 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
	Transformer des coordonnées 3D (x, y, z) en coordonnées 2D écran (projection)
	- Calculer un point projeté avec zoom, tile_size... (get_projected_point)
	- Relier les points adj de la grille en appelant draw_line (draw_connections)
	- Appliquer la projection isométrique (project_iso)
*/

t_point	get_projected_point(t_point p, t_engine *engine)
{
	t_point	projected;

	projected = p;
	projected.x = p.x * engine->camera.tile_size * engine->camera.zoom;
	projected.y = p.y * engine->camera.tile_size * engine->camera.zoom;
	projected.z = p.z * engine->camera.z_scale * engine->camera.zoom;
	project_iso(&projected.x, &projected.y, projected.z);
	projected.x += engine->camera.x_offset;
	projected.y += engine->camera.y_offset;
	projected.color = p.color;
	return (projected);
}

void	draw_connections(t_engine *engine, int x, int y)
{
	t_point	p1;
	t_point	p2;

	p1 = get_projected_point(engine->map.grid[y][x], engine);
	if (x < engine->map.width - 1)
	{
		p2 = get_projected_point(engine->map.grid[y][x + 1], engine);
		draw_line(engine, p1, p2);
	}
	if (y < engine->map.height - 1)
	{
		p2 = get_projected_point(engine->map.grid[y + 1][x], engine);
		draw_line(engine, p1, p2);
	}
}

void	project_iso(int *x, int *y, int z)
{
	int	x_old;
	int	y_old;

	x_old = *x;
	y_old = *y;
	*x = (x_old - y_old) * cos(ISO_ANGLE);
	*y = (x_old + y_old) * sin(ISO_ANGLE) - z;
}
