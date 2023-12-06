/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:49 by sschelti          #+#    #+#             */
/*   Updated: 2023/12/06 18:08:47 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>

t_player	*player_init(mlx_t *mlx)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->x_pos = 5.0;
	player->y_pos = 5.0;
	player->x_dir = 1;
	player->y_dir = 0;
	player->x_plane = 0;
	player->y_plane = 0.66;
	player->time = 0;
	player->oldtime = 0;
	player->mlx = mlx;
	return (player);
}
