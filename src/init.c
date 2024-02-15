/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/08 13:59:31 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/15 17:08:01 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	(*map)->start_dir = 0;
	(*map)->map = ft_malloc(sizeof(int *) * (*map)->height);
	while (i < (*map)->height)
	{
		(*map)->map[i] = ft_malloc(sizeof(int) * (*map)->width);
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
		exit_error("Error\nMultiple starting positions\n");
}
