/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:40:12 by sschelti          #+#    #+#             */
/*   Updated: 2023/12/08 17:34:28 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    calculate_delta_dist(t_ray *ray)
{
    if (ray->x_dir == 0)
        ray->x_dir = 1e30;
    if (ray->y_dir == 0)
        ray->y_dir = 1e30;
    ray->delta_dist_x = sqrt(1 + pow(ray->y_dir/ray->x_dir, 2));
    ray->delta_dist_y = sqrt(1 + pow(ray->x_dir/ray->y_dir, 2));
}

void    calculate_step_side_dist(t_player *player, t_ray *ray)
{
        player->x_map = (int)player->x_pos;
        player->y_map = (int)player->y_pos;
}

void    raycasting(t_player *player)
{
    t_ray ray;
    double cameraX;
    double x;

    cameraX = 0;
    x = 0;
    while (x < WIDTH)
    {
        cameraX = 2 * x / (double)WIDTH - 1;
        ray.x_dir = player->x_dir + player->x_plane * cameraX;
        ray.y_dir = player->y_dir + player->y_plane * cameraX;
        calculate_delta_dist(&ray);
        calculate_step_side_dist(player, &ray);
        x++;
    }
}