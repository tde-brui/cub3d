/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:49 by sschelti          #+#    #+#             */
/*   Updated: 2024/02/17 14:58:02 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>

void determine_start_dir(t_player *player)
{
	if (player->map->start_dir == 'N')
	{
		player->x_dir = 0;
		player->y_dir = -1;
		player->x_plane = 0.66;
		player->y_plane = 0;
	}
	else if (player->map->start_dir == 'S')
	{
		player->x_dir = 0;
		player->y_dir = 1;
		player->x_plane = -0.66;
		player->y_plane = 0;
	}
	else if (player->map->start_dir == 'E')
	{
		player->x_dir = 1;
		player->y_dir = 0;
		player->x_plane = 0;
		player->y_plane = 0.66;
	}
	else if (player->map->start_dir == 'W')
	{
		player->x_dir = -1;
		player->y_dir = 0;
		player->x_plane = 0;
		player->y_plane = -0.66;
	}
}

void	player_init(t_player **player, mlx_t *mlx, mlx_image_t *image, t_map *map)
{
	(*player) = malloc(sizeof(t_player));
	if (!(*player))
		cleanup_error(map, MALLOC_FAIL);
	(*player)->map = map;
	determine_start_dir((*player));
	(*player)->x_pos = (*player)->map->start_pos_x + 0.5;
	(*player)->y_pos = (*player)->map->start_pos_y + 0.5;
	(*player)->mlx = mlx;
	(*player)->image = image;
}
