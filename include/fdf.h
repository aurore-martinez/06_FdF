/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:20:33 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 16:10:18 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/gnl/get_next_line_bonus.h"
# include "../lib/ft_bool/ft_boolean.h"
# include "../minilibx-linux/mlx.h"
# include "keys.h"

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define WIN_WIDTH     1400
# define WIN_HEIGHT    1000
# define ISO_ANGLE     0.523599  // ~30° en radians
# define VIEW_CHANGE_STEP 20
# define ZOOM_FACTOR 1.1

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	t_point	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr_ptr;
	int		pixel_bits;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_camera
{
	float	zoom;
	int		x_offset;
	int		y_offset;
	int		color;
	int		z_scale;
	int		tile_size;
}	t_camera;

typedef struct s_engine
{
	void		*mlx;
	void		*window;
	t_image		image;
	t_map		map;
	t_camera	camera;
}	t_engine;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_bresenham;

/* Dessin et Projection */
void			draw_line(t_engine *engine, t_point a, t_point b_point);
void			draw_connections(t_engine *engine, int x, int y);
void			project_iso(int *x, int *y, int z);
t_point			get_projected_point(t_point p, t_engine *engine);

void			init_engine(t_engine *engine, char *filename);
void			render_map(t_engine *engine);
void			init_camera(t_camera *camera);

/* Map Parsing */
void			get_map_size(char *filename, t_map *map);
void			fill_grid(char *filename, t_map *map);
void			free_grid(t_point	**grid);
void			parse_map(char *filename, t_map *map);

// Events
int				on_key_press(int key, t_engine *engine);
int				on_destroy_event(void *param);

// Utils
void			error_message(char *msg, int mode);
int				word_count(char *str, char c);
void			show_help(void);
int				ft_atoi_base(char *str, int base);

/* Bonus */
void			change_view(int key, t_engine *engine);
void			change_color(int key, t_engine *engine);
int				get_z_range(t_map *map);
int				determine_z_scale(t_map *map);
int				determine_tile_size(t_map *map);

#endif
