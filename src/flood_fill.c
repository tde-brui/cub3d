/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/16 16:47:15 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/17 13:24:43 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include <stdio.h>

// int	flood_fill(t_map *map, int row, int col)
// {
// 	if (row < 0 || row >= map->height || col < 0 || col >= map->width)
// 		return (0);
// 	if (map->map[row][col] == 0)
// 	{
// 		map->map[row][col] = 2;
// 		flood_fill(map, row + 1, col);
// 		flood_fill(map, row - 1, col);
// 		flood_fill(map, row, col + 1);
// 		flood_fill(map, row, col - 1);
// 		return (1);
// 	}
// 	return (0);
// }

// int	look_for_zeros(t_map *map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map->height)
// 	{
// 		j = 0;
// 		while (j < map->width)
// 		{
// 			if (map->map[i][j] == 0)
// 				return (1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	flood_from_sides(t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	while (i < map->height)
// 	{
// 		flood_fill(map, i, 0);
// 		flood_fill(map, i, map->width - 1);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < map->width)
// 	{
// 		flood_fill(map, 0, i);
// 		flood_fill(map, map->height - 1, i);
// 		i++;
// 	}
// 	if (look_for_zeros(map))
// 		return (0);
// 	return (1);
// }

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
			|| flood_fill_start(map_copy, row - 1, col)
			|| flood_fill_start(map_copy, row, col + 1)
			|| flood_fill_start(map_copy, row, col - 1));
	}
	return (0);
}

//need to make a map_copy because flood fill needs to mark the map
int	flood_from_start(t_map *map)
{
	t_map	*map_copy;
	int		i;
	int		j;

	map_copy = malloc(sizeof(t_map));
	map_copy->map = malloc(sizeof(int *) * map->height);
	map_copy->height = map->height;
	map_copy->width = map->width;
	i = 0;
	while (i < map->height)
	{
		map_copy->map[i] = malloc(sizeof(int) * map->width);
		j = 0;
		while (j < map->width)
		{
			map_copy->map[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
	if (flood_fill_start(map_copy, map->start_pos_y, map->start_pos_x))
		return (ft_free_map_copy(map_copy), 1);
	return (ft_free_map_copy(map_copy), 0);
}
