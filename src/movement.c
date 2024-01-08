/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:32:17 by stijn             #+#    #+#             */
/*   Updated: 2024/01/05 13:14:34 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//rotates player using a angle between 0 and 2 * PI.
//to do: rotate camera plane and direction vector with same angle using rotation matrix
void    rotate_player(double delta_angle, t_player *player)
{
    double x_p = player->x_plane;
    double y_p = player->y_plane;
    double x_d = player->x_dir;
    double y_d = player->y_dir;
        
    // player->x_dir = cos(player->angle);
    // player->y_dir = sin(player->angle);
    player->x_plane = x_p * cos(delta_angle) - y_p * sin(delta_angle);
    player->y_plane = x_p * sin(delta_angle) + y_p * cos(delta_angle);
    player->x_dir = x_d * cos(delta_angle) - y_d * sin(delta_angle);
    player->y_dir = x_d * sin(delta_angle) + y_d * cos(delta_angle);
}

void    move_player(double sign, t_player *player)
{
    int tempx;
    int tempy;
    
    tempx = player->x_pos + player->x_dir * 0.02 * sign;
    tempy = player->y_pos + player->y_dir * 0.02 * sign;
    printf("tempx: %d, tempy: %d\n", tempx, tempy);
    printf("xpos: %f, ypos: %f\n", player->x_pos, player->y_pos);
    if (!player->map->map[tempy][tempx])
    {
        player->x_pos += player->x_dir * 0.02 * sign;
        player->y_pos += player->y_dir * 0.02 * sign;
    }
}
