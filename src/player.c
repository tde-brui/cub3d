/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:05:49 by sschelti          #+#    #+#             */
/*   Updated: 2023/12/04 17:50:26 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_player	*player_init(mlx_t *mlx)
{
	t_player	*player;

	player = malloc(sizeof(player));
	player->x_pos = 5;
	player->y_pos = 5;
	player->mlx = mlx;
	return (player);
}
