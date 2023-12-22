#include "../inc/cub3d.h"

void    draw_wall(t_player *player, t_ray *ray, int x)
{
    int line_height = (double)HEIGHT / ray->player_distance;
    printf("line height:%d\n", line_height);
    if (line_height > 512)
        line_height = 512;
    int draw_start = line_height / 2 - line_height / 2;
    int draw_end = line_height / 2 + line_height / 2;
    for (int y = draw_start; y != draw_end; y++)
        mlx_put_pixel(player->image, x, y, get_colour(255, 0, 0, 255));
}
