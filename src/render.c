/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:40:03 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 10:40:04 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
