/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aumartin <aumartin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:40:00 by aumartin          #+#    #+#             */
/*   Updated: 2025/04/04 13:58:27 by aumartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

void	parse_map(char *filename, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("[FILE ERROR]: failed to open map\n", 0);
	map->height = 0;
	map->width = 0;
	while ((line = get_next_line(fd)))
	{
		if (map->height == 0)
			map->width = word_count(line, ' ');
		map->height++;
		free(line);
	}
	close(fd);
	map->grid = alloc_grid(map->width, map->height);
	fd = open(filename, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		parse_line(line, map->grid[i], i);
		free(line);
		i++;
	}
	close(fd);
}
