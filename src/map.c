/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 16:33:58 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/08 13:25:32 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include <stdio.h>

void	init_rgb(t_rgb *rgb)
{
	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
	rgb->colour = 0;
}

void	init_textures(t_map *map)
{
	int	i;

	map->textures = ft_malloc(sizeof(t_texture) * 6);
	i = 0;
	while (i != 6)
	{
		map->textures[i].direction = i;
		map->textures[i].path = NULL;
		map->textures[i].texture_mlx = NULL;
		map->textures[i].colour = ft_malloc(sizeof(t_rgb));
		init_rgb(map->textures[i].colour);
		i++;
	}
}

void	map_init(t_map **map, char *cub)
{
	int	i;

	i = 0;
	*map = ft_malloc(sizeof(t_map));
	init_textures(*map);
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
	return (ft_strlen(line) - 1);
}

void	parse_map(char *line, t_map *map, int i, char *cub)
{
	int	j;
	int	width;

	j = 0;
	printf("%s\n", line);
	width = determine_width(map, i, line);
	while (j < width)
	{
		if (line[j] == 'N' || line[j] == 'E'
			|| line[j] == 'S' || line[j] == 'W')
		{
			map->start_pos_x = j;
			map->start_pos_y = i;
			map->start_dir = line[j];
			map->map[i][j] = 0;
		}
		else if (line[j] == '1' || line[j] == '0')
			map->map[i][j] = line[j] - 48;
		else if (ft_isspace(line[j]))
			map->map[i][j] = 0;
		else
			exit_error("Error\nInvalid character in map\n");
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
	int	i;
	int	j;

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
