#include "../inc/cub3d.h"

void    calculate_wall_height(t_ray *ray)
{
    int wall_height = (double)HEIGHT / ray->player_distance;
    ray->draw_start = HEIGHT / 2 - wall_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = HEIGHT / 2 + wall_height / 2;
    if (ray->draw_end > HEIGHT)
        ray->draw_end = HEIGHT;
    ray->wall_height = wall_height;
}

static uint32_t    get_colour_pixels(int x, int y, t_texture *texture)
{
    int         index;
    uint8_t     *ptr;
    uint32_t    ret = 0;

    index = (texture->texture_mlx->width * y + x) * sizeof(int);
    ptr = &(texture->texture_mlx->pixels[index]);
    ret += (uint32_t)*ptr++ << 24;
    ret += (uint32_t)*ptr++ << 16;
    ret += (uint32_t)*ptr++ << 8;
    ret += (uint32_t)255;
    return (ret);
}
/*calculate the wall height. then determine the x value where the ray hit (0 - 1).
*/
void    draw_wall(t_player *player, t_ray *ray, int x)
{
    t_texture   *texture;

    texture = &player->map->textures[select_texture(ray)];
    calculate_texture_x(ray, player);
    calculate_wall_height(ray);
    double step = 1.0 * texture->texture_mlx->height / ray->wall_height;
    double texPos = (ray->draw_start - HEIGHT / 2 + ray->wall_height / 2) * step;
    uint32_t colour = 0;
    for (int y = ray->draw_start; y != ray->draw_end; y++)
    {
        int texy = (int)texPos & (texture->texture_mlx->height - 1);
        texPos += step;
        colour = get_colour_pixels(ray->texture_x, texy, texture);
        player->screen_buffer[y][x] = colour;
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
