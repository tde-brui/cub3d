/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 17:05:49 by sschelti      #+#    #+#                 */
/*   Updated: 2024/01/12 16:59:04 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>

void	determine_start_dir(t_map *map, t_player *player)
{
	if (map->start_dir == 'N')
	{
		player->x_dir = 0;
		player->y_dir = -1;
	}
	else if (map->start_dir == 'E')
	{
		player->x_dir = 1;
		player->y_dir = 0;
	}
	else if (map->start_dir == 'S')
	{
		player->x_dir = 0;
		player->y_dir = 1;
	}
	else if (map->start_dir == 'W')
	{
		player->x_dir = -1;
		player->y_dir = 0;
	}
}

t_player	*player_init(mlx_t *mlx, mlx_image_t *image, t_map *map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->x_pos = map->start_pos_x;
	player->y_pos = map->start_pos_y;
	determine_start_dir(map, player);
	player->x_plane = 0.66;
	player->y_plane = 0;
	player->time = 0;
	player->oldtime = 0;
	player->mlx = mlx;
	player->image = image;
	player->map = map;
	return (player);
}
