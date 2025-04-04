/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:40:12 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 10:40:13 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (argc != 2)
		show_help();
	init_engine(&engine, argv[1]);
	render_map(&engine);
	mlx_key_hook(engine.window, on_key_press, &engine);
	mlx_hook(engine.window, 17, 0, on_destroy_event, &engine);
	mlx_loop(engine.mlx);
	return (0);
}
