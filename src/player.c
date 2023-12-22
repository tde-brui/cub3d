/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 17:05:49 by sschelti      #+#    #+#                 */
/*   Updated: 2023/12/21 16:18:02 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdio.h>

void	determine_player_dir(t_player *player, t_map *map)
{
	if (map->start_dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
	}
	else if (map->start_dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	else if (map->start_dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
	}
	else if (map->start_dir == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
	}
}

void set_plane(t_map *map, t_player *player)
{
	if (map->start_dir == 'N' || map->start_dir == 'S')
	{
		player->plane.x = 0;
		if (map->start_dir == 'N')
			player->plane.y = -1;
		else
			player->plane.y = 1;
	}
	else if (map->start_dir == 'E' || map->start_dir == 'W')
	{
		player->plane.y = 0;
		if (map->start_dir == 'E')
			player->plane.x = 1;
		else
			player->plane.x = -1;
	}
}

t_player	*player_init(mlx_t *mlx, t_map *map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos.x = map->start_pos_x;
	player->pos.y = map->start_pos_y;
	determine_player_dir(player, map);
	set_plane(map, player);
	player->x_map = (int)player->pos.x;
	player->y_map = (int)player->pos.y;
	player->time = 0;
	player->oldtime = 0;
	player->mlx = mlx;
	return (player);
}
