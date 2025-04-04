/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:05:44 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 16:11:21 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* point->color = -1; défaut */
static void	parse_token(char *token, t_point *point, int x, int y)
{
	char	**parts;

	parts = ft_split(token, ',');
	point->x = x;
	point->y = y;
	point->z = ft_atoi(parts[0]);
	point->color = -1;
	if (parts[1])
		point->color = ft_atoi_base(parts[1], 16);
	free(parts[0]);
	if (parts[1])
		free(parts[1]);
	free(parts);
}

/* printf("Parsed color: %s -> %06X\n", parts[1], point->color); */

static int	parse_line(char *line, t_point *row, int y)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		error_message("[PARSE ERROR]: ft_split failed\n", 1);
	i = 0;
	while (split[i])
	{
		parse_token(split[i], &row[i], i, y);
		free(split[i]);
		i++;
	}
	free(split);
	return (i);
}

/* Détermine la largeur et la hauteur de la carte */
void	get_map_size(char *filename, t_map *map)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("[FILE ERROR]: failed to open map\n", 0);
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map->height == 0)
			map->width = word_count(line, ' ');
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

/* Remplit la grille avec les points de la carte */
void	fill_grid(char *filename, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("[FILE ERROR]: failed to reopen map\n", 0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, map->grid[i], i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}
