/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 17:05:49 by sschelti      #+#    #+#                 */
/*   Updated: 2023/12/12 14:43:11 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdio.h>

int	determine_start_dir(t_map *map, t_player *player)
{
	if (map->start_dir == 'N')
	{
		player->x_dir = -1;
		player->y_dir = 0;
	}
	else if (map->start_dir == 'S')
	{
		player->x_dir = 1;
		player->y_dir = 0;
	}
	else if (map->start_dir == 'W')
	{
		player->x_dir = 0;
		player->y_dir = -1;
	}
	else if (map->start_dir == 'E')
	{
		player->x_dir = 0;
		player->y_dir = 1;
	}
	else
		return (1);
	return (0);
}

t_player	*player_init(mlx_t *mlx, t_map *map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->x_pos = map->start_pos_x;
	player->y_pos = map->start_pos_y;
	if (determine_start_dir(map, player))
		return (NULL);
	player->x_plane = 0.66;
	player->y_plane = 0;
	player->x_map = (int)player->x_pos;
	player->y_map = (int)player->y_pos;
	player->time = 0;
	player->oldtime = 0;
	player->mlx = mlx;
	return (player);
}
