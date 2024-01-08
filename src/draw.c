#include "../inc/cub3d.h"

void    draw_wall(t_player *player, t_ray *ray, int x)
{
    int line_height = (double)HEIGHT / ray->player_distance;
    if (line_height > 512)
        line_height = 512;
    int draw_start = HEIGHT / 2 - line_height / 2;
    int draw_end = HEIGHT / 2 + line_height / 2;
    for (int y = draw_start; y != draw_end; y++)
        mlx_put_pixel(player->image, x, y, get_colour(255, 0, 0, 255));
}

void    draw_background(t_player *player)
{
    for (int x = 0; x != WIDTH; x++)
        for (int y = 0; y != HEIGHT; y++)
            mlx_put_pixel(player->image, x, y, 0);
}