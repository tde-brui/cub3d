/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:32:17 by stijn             #+#    #+#             */
/*   Updated: 2023/12/20 19:13:24 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//rotates player using a angle between 0 and 2 * PI.
//to do: rotate camera plane and direction vector with same angle using rotation matrix
void    rotate_player(double delta_angle, t_player *player)
{
    player->angle += delta_angle;
    if (player->angle < 0)
        player->angle += 2 * PI;
    else if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    player->delta_x = cos(player->angle);
    player->delta_y = sin(player->angle);
    printf("dx: %f, dy: %f\n", player->delta_x, player->delta_y);
}

void    move_player(double sign, t_player *player)
{
    player->x_pos += player->delta_x * 0.02 * sign;
    player->y_pos += player->delta_y * 0.02 * sign;
}
