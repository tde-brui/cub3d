#include "../inc/cub3d.h"

void    calculate_wall_height(t_ray *ray)
{
    int wall_height = (double)HEIGHT / ray->player_distance;
    if (wall_height > 512)
        wall_height = 512;
    int draw_start = HEIGHT / 2 - wall_height / 2;
    int draw_end = HEIGHT / 2 + wall_height / 2;
    ray->wall_height = wall_height;
}

/*calculate the wall height. then determine the x value where the ray hit (0 - 1).
*/
void    draw_wall(t_player *player, t_ray *ray, int x)
{
    calculate_wall_height(ray);
    calculate_texture_x(ray, player);
}

void    draw_background(t_player *player)
{
    uint32_t *ceiling_colour;
    uint32_t *floor_colour;

    ceiling_colour = &player->map->textures[CEILING].colour->colour;
    floor_colour = &player->map->textures[FLOOR].colour->colour;
    for (int y = 0; y != HEIGHT / 2; y++)
        for (int x = 0; x != WIDTH; x++)
            player->screen_buffer[y][x] = *ceiling_colour;
    // mlx_put_pixel(player->image, x, y, *ceiling_colour);
    for (int y = HEIGHT / 2; y != HEIGHT; y++)
        for (int x = 0; x != WIDTH; x++)
            player->screen_buffer[y][x] = *floor_colour;
}

void    buffer_to_image(t_player *player)
{
    for (int x = 0; x != WIDTH; x++)
        for (int y = 0; y != HEIGHT; y++)
            mlx_put_pixel(player->image, x, y, player->screen_buffer[y][x]);
}
