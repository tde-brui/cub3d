/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:59:31 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/22 18:10:18 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/parse.h"

static void	allocate_map_array(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	map->map = malloc(sizeof(int *) * map->height);
	if (!map->map)
		cleanup_error(map, MALLOC_FAIL);
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(int) * map->width);
		if (!map->map[i])
		{
			while (j < i)
			{
				free(map->map[i]);
				map->map[i] = NULL;
				j++;
			}
			cleanup_error(map, MALLOC_FAIL);
		}
		i++;
	}
}

void	config_start_pos(t_map *map, int i, int j, char direction)
{
	if (!map->start_dir)
	{
		map->start_pos_x = j;
		map->start_pos_y = i;
		map->start_dir = direction;
		map->map[i][j] = 0;
	}
	else
		exit_error(MULTIPLE_START_POS);
}

static void	init_textures(t_map *map)
{
	unsigned int		i;

	i = 0;
	map->textures = malloc(sizeof(t_texture) * NUM_OF_TEXTURES);
	if (!map->textures)
		cleanup_error(map, MALLOC_FAIL);
	while (i != NUM_OF_TEXTURES)
	{
		map->textures[i].direction = i;
		map->textures[i].path = NULL;
		map->textures[i].texture_mlx = NULL;
		map->textures[i].colour = 0;
		i++;
	}
}

int	map_init(t_map *map, char *cub_file, mlx_t *mlx)
{
	map->mlx = mlx;
	map->textures = NULL;
	map->map = NULL;
	map->start_dir = '\0';
	init_textures(map);
	get_map_dimensions(map, cub_file);
	allocate_map_array(map);
	return (0);
}
