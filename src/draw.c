/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:11:12 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/19 14:37:47 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calculate_wall_height(t_ray *ray)
{
	int	wall_height;

	wall_height = (double)HEIGHT / ray->player_distance;
	ray->draw_start = HEIGHT / 2 - wall_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = HEIGHT / 2 + wall_height / 2;
	if (ray->draw_end > HEIGHT)
		ray->draw_end = HEIGHT;
	ray->wall_height = wall_height;
}

static uint32_t	get_colour_pixels(int x, int y, t_texture *texture)
{
	int			index;
	uint8_t		*ptr;
	uint32_t	ret;

	ret = 0;

	index = (texture->texture_mlx->width * y + x) * sizeof(int);
	ptr = &(texture->texture_mlx->pixels[index]);
	ret += (uint32_t)*ptr++ << 24;
	ret += (uint32_t)*ptr++ << 16;
	ret += (uint32_t)*ptr++ << 8;
	ret += (uint32_t)255;
	return (ret);
}
/*calculate the wall height. 
then determine the x value where the ray hit (0 - 1).
*/

void	draw_wall(t_player *player, t_ray *ray, int x)
{
	t_texture	*texture;
	double		step;
	double		texpos;
	uint32_t	colour;

	texture = &player->map->textures[select_texture(ray)];
	calculate_texture_x(ray, player);
	calculate_wall_height(ray);
	step = 1.0 * texture->texture_mlx->height / ray->wall_height;
	texpos = (ray->draw_start - HEIGHT / 2 + ray->wall_height / 2) * step;
	colour = 0;
	for (int y = ray->draw_start; y != ray->draw_end; y++)
	{
		int texy = (int)texpos & (texture->texture_mlx->height - 1);
		texpos += step;
		colour = get_colour_pixels(ray->texture_x, texy, texture);
		player->screen_buffer[y][x] = colour;
	}

}

void	buffer_to_image(t_player *player)
{
	int	x;
	int	y;

	x = 0;
	while (x != WIDTH)
	{
		y = 0;
		while (y != HEIGHT)
		{
			mlx_put_pixel(player->image, x, y, player->screen_buffer[y][x]);
			y++;
		}
		x++;
	}
}
