/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 16:47:15 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/03/07 17:24:56 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"
#include <stdio.h>

int	flood_fill_start(t_map *map_copy, int row, int col)
{
	if (row < 0 || row >= map_copy->height || col < 0 || col >= map_copy->width)
		return (1);
	if (map_copy->map[row][col] == 1)
		return (0);
	if (map_copy->map[row][col] == 0)
	{
		map_copy->map[row][col] = 2;
		return (flood_fill_start(map_copy, row + 1, col)
			|| flood_fill_start(map_copy, row - 1, col + 1)
			|| flood_fill_start(map_copy, row - 1, col)
			|| flood_fill_start(map_copy, row - 1, col - 1)
			|| flood_fill_start(map_copy, row, col + 1)
			|| flood_fill_start(map_copy, row + 1, col + 1)
			|| flood_fill_start(map_copy, row, col - 1))
			|| flood_fill_start(map_copy, row + 1, col - 1);
	}
	return (0);
}

static t_map	*allocate_map_copy(t_map *map)
{
	t_map	*map_copy;

	map_copy = malloc(sizeof(t_map));
	if (!map_copy)
		cleanup_error(map, MALLOC_FAIL);
	map_copy->map = malloc(sizeof(int *) * map->height);
	if (!map_copy->map)
	{
		free(map_copy);
		cleanup_error(map, MALLOC_FAIL);
	}
	map_copy->height = map->height;
	map_copy->width = map->width;
	return (map_copy);
}

//need to make a map_copy because flood fill needs to mark the map
int	flood_from_start(t_map *map)
{
	t_map	*map_copy;
	int		i;
	int		j;

	map_copy = allocate_map_copy(map);
	i = 0;
	while (i < map->height)
	{
		map_copy->map[i] = malloc(sizeof(int) * map->width);
		if (!map_copy->map[i])
		{
			ft_free_map_copy(map_copy, i);
			cleanup_error(map, MALLOC_FAIL);
		}
		j = 0;
		while (j < map->width)
		{
			map_copy->map[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
	if (flood_fill_start(map_copy, map->start_pos_y, map->start_pos_x))
		return (ft_free_map_copy(map_copy, i), 1);
	return (ft_free_map_copy(map_copy, i), 0);
}
