/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:42:57 by sschelti          #+#    #+#             */
/*   Updated: 2023/12/21 14:51:55 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    dda(t_player *player, t_ray *ray)
{
    int hit = 0;

    while (!hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->x_map += ray->stepx;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->y_map += ray->stepy;
            ray->side = 1;
        }
        if (player->map->map[ray->y_map][ray->x_map])
            hit = 1;
    }
}