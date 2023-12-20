/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:33:58 by tde-brui          #+#    #+#             */
/*   Updated: 2023/12/20 18:10:40 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include <stdio.h>

void	init_rgb(t_rgb *rgb)
{
	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
}

void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->east = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->floor = ft_malloc(sizeof(t_rgb));
	textures->ceiling = ft_malloc(sizeof(t_rgb));
	init_rgb(textures->floor);
	init_rgb(textures->ceiling);
}

void	map_init(t_map **map, char *cub)
{
	int	i;

	i = 0;
	*map = ft_malloc(sizeof(t_map));
	(*map)->textures = ft_malloc(sizeof(t_textures));
	init_textures((*map)->textures);
	(*map)->width = get_max_width(cub);
	(*map)->height = get_height(cub);
	printf("max width: %d\n", (*map)->width);
	printf("height: %d\n", (*map)->height);
	(*map)->map = ft_malloc(sizeof(int *) * (*map)->height);
	while (i < (*map)->height)
	{
		(*map)->map[i] = ft_malloc(sizeof(int) * (*map)->width);
		i++;
	}
}

int	determine_width(t_map *map, int i, char *line)
{
	if (map->height == i + 1)
		return (ft_strlen(line));
	return (ft_strlen(line) - 1);
}

void	parse_map(char *line, t_map *map, int i, char *cub)
{
	int	j;
	int	width;

	j = 0;
	while (line[j] == ' ')
	{
		map->map[i][j] = 0;
		j++;
	}
	width = determine_width(map, i, line);
	printf("width: %d\n", width);
	while (j < width)
	{
		if (line[j] == 'N' || line[j] == 'E'
			|| line[j] == 'S' || line[j] == 'W')
		{
			map->start_pos_x = j;
			map->start_pos_y = i;
			map->map[i][j] = 50;
		}
		else if (line[j] == '1' || line[j] == '0')
			map->map[i][j] = line[j] - 48;
		else if (line[j] == ' ')
			map->map[i][j] = 0;
		j++;
	}
	while (j < map->width)
	{
		map->map[i][j] = 0;
		j++;
	}
}

void	print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%d ", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
