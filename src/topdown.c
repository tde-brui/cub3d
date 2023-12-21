/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topdown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:06:15 by stijn             #+#    #+#             */
/*   Updated: 2023/12/21 15:20:44 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void create_square(int x, int y, t_player *player, int size, int colour)
{
    for (int j = x; j <= (x + size); j++)
        for (int i = y; i <= (y + size); i++)
            mlx_put_pixel(player->image, j, i, colour);
}

void    draw_background(t_player *player)
{
    int **map = player->map->map;
    
    for (int x = 0; x != 8; x++)
    {   
        for (int y = 0; y != 8; y++)
        {
            if (map[y][x])
                create_square((x * 64), (y * 64), player, 64, get_colour(255, 255, 0, 255));
            else
                create_square((x * 64), (y * 64), player, 64, get_colour(0, 0, 0, 255));
        }
    }
}

void    draw_player(t_player *player)
{
    map_coordinate_to_pixel(player, player->x_pos, player->y_pos, get_colour(255, 0, 0, 255));
}

void draw_vector(t_player *player, t_ray *ray)
{
    double length;

    if (ray->side == 0)
        length = ray->side_dist_x - ray->delta_dist_x;
    else
        length = ray->side_dist_y - ray->delta_dist_y;
    
    for (double i = 0; i <= length; i += 0.01)
    {
        double x = player->x_pos + i * ray->x_dir;
        double y = player->y_pos + i * ray->y_dir;
        map_coordinate_to_pixel(player, x, y, get_colour(0, 255, 0, 255));
    }
}

//converts a value in the map x,y coordinate system to a pixel value
void map_coordinate_to_pixel(t_player *player, double x_cor, double y_cor, uint32_t colour)
{
    double max_width = (double)player->map->width;
    double max_height = (double)player->map->height;
    int x = (x_cor / max_width) * (double)WIDTH;
    int y = (y_cor / max_height) * (double)HEIGHT;
    x = (x % 512 + 512) % 512;
    y = (y % 512 + 512) % 512;
    mlx_put_pixel(player->image, x, y, colour);
}
