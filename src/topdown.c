/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topdown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:06:15 by stijn             #+#    #+#             */
/*   Updated: 2023/12/14 20:26:25 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void create_square(int x, int y, t_player *player)
{
    for (int j = (x - 2); j <= (x + 2); j++)
        for (int i = (y - 2); i <= (y + 2); i++)
            mlx_put_pixel(player->image, j, i, get_colour(0, 255, 0, 255));
}

void    draw_background(t_player *player)
{
    for (int x = 0; x != WIDTH; x++)
        for (int y = 0; y != HEIGHT; y++)
            mlx_put_pixel(player->image, x, y, 0);
}

void    draw_player(t_player *player)
{
    
    double max_width = (double)player->map->width;
    double max_height = (double)player->map->height;
    int x = (player->x_pos / max_width) * (double)WIDTH;
    int y = (player->y_pos / max_height) * (double)HEIGHT;
    x = x % 512;
    y = y % 512;
    printf("x: %d, y: %d\n", x, y);
    create_square(x, y, player);
}