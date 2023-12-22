/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:40:12 by sschelti          #+#    #+#             */
/*   Updated: 2023/12/22 15:44:34 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//calculates the distance the ray travels for 1 step x and 1 step y
void    calculate_delta_dist(t_ray *ray)
{
    if (ray->x_dir == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1 / ray->x_dir);
    if (ray->y_dir == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1 / ray->y_dir);
}

/*Calculates side step distance by multiplying the distance of the player 
to the wall the ray crosses by DeltaDist.*/
void    calculate_step_side_dist(t_player *player, t_ray *ray)
{
    ray->x_map = (int)player->x_pos;
    ray->y_map = (int)player->y_pos;
    if (ray->x_dir > 0)
    {
        ray->stepx = 1;
        ray->side_dist_x = (ray->x_map + 1.0 - player->x_pos) * ray->delta_dist_x;
    }
    else
    {
        ray->stepx = -1;
        ray->side_dist_x = (player->x_pos - ray->x_map) * ray->delta_dist_x;
    }
    if (ray->y_dir > 0)
    {
        ray->stepy = 1;
        ray->side_dist_y = (ray->y_map + 1.0 - player->y_pos) * ray->delta_dist_y;
    }
    else
    {
        ray->stepy = -1;
        ray->side_dist_y = (player->y_pos - ray->y_map) * ray->delta_dist_y;
    }
}

//function called everytime a hook is activated
//creates a ray for every x pixel on the screen
void    raycasting(t_player *player)
{
    t_ray ray;
    double cameraX;
    int x;

    cameraX = 0;
    x = 0;
    // draw_background_topdown(player);
    // draw_player_topdown(player);
    draw_background(player);
    while (x < WIDTH)
    {
        cameraX = 2 * x / (double)WIDTH - 1;
        ray.x_dir = player->x_dir + player->x_plane * cameraX;
        ray.y_dir = player->y_dir + player->y_plane * cameraX;
        calculate_delta_dist(&ray);
        calculate_step_side_dist(player, &ray);
        dda(player, &ray);
        calculate_player_distance(&ray);
        // draw_vector(player, &ray);
        draw_wall(player, &ray, x);
        // calculate distance from camera plane
        // draw x amount of pixels depending on the distance to the camera plane
        x++;
    }
}