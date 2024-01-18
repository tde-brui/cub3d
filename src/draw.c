#include "../inc/cub3d.h"

void    calculate_wall_height(t_ray *ray)
{
    int wall_height = (double)HEIGHT / ray->player_distance;
    if (wall_height > 512)
        wall_height = 512;
    ray->draw_start = HEIGHT / 2 - wall_height / 2;
    ray->draw_end = HEIGHT / 2 + wall_height / 2;
    ray->wall_height = wall_height;
}

static uint32_t    get_colour_pixels(int x, int y, t_texture *texture)
{
    uint32_t    ret;
    int         bitshift = 24;

    for (int i = 0; i != 4; i++)
    {
        ret = texture->texture_mlx->pixels[x * y + i] << bitshift;
        bitshift -= 8;
    }
    return (ret);
}
/*calculate the wall height. then determine the x value where the ray hit (0 - 1).
*/
void    draw_wall(t_player *player, t_ray *ray, int x)
{
    t_texture   *texture;
    uint32_t    colour;    

    texture = &player->map->textures[select_texture(ray)];
    calculate_texture_x(ray, player, texture);
    calculate_wall_height(ray);
    double step = (double)ray->wall_height/ (double)HEIGHT;
    double texture_y = 0.0;
    for (int y = ray->draw_start; y != ray->draw_end; y++)
    {
        colour = get_colour_pixels(ray->texture_x, (int)texture_y, texture);
        texture_y += 1.0;
        player->screen_buffer[x][y] = colour;
    }

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
