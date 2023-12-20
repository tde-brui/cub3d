/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:40:12 by sschelti      #+#    #+#                 */
/*   Updated: 2023/12/20 18:21:43 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_ray(t_player *player, t_ray *ray, double cameraX)
{
	ray->dir.x = player->dir.x + player->plane.x * cameraX;
	ray->dir.y = player->dir.y + player->plane.y * cameraX;
	ray->x_map = (int)player->pos.x;
	ray->y_map = (int)player->pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
}

void	determine_side_dist(t_player *player, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (player->pos.x - ray->x_map) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->x_map + 1.0 - player->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (player->pos.y - ray->y_map) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->y_map + 1.0 - player->pos.y) * ray->delta_dist.y;
	}
}

void	dda(t_player *player, t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->x_map += ray->step_x;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->y_map += ray->step_y;
		}
		printf("x_map: %d, y_map: %d\n", ray->x_map, ray->y_map);
		if (map->map[ray->y_map][ray->x_map] == 1)
			ray->hit = 1;
	}
}

void determine_wall_height(t_player *player, t_ray *ray)
{
	int ray_height;

	ray_height = HEIGHT / ray->distance_to_wall;
	ray->top_pixel = (HEIGHT - ray_height) / 2;
	ray->bottom_pixel = (HEIGHT + ray_height) / 2;
}

void	raycasting(t_player *player, t_map *map, mlx_image_t *image)
{
	int		i;
	double camera;
	t_ray	ray;

	i = 0;
	while (i < WIDTH)
	{
		camera = 2 * i / (double)WIDTH - 1;
		init_ray(player, &ray, camera);
		determine_side_dist(player, &ray);
		dda(player, &ray, map);
		if (ray.side_dist.x < ray.side_dist.y)
			ray.distance_to_wall = (ray.x_map - player->pos.x + (1 - ray.step_x) / 2) / ray.dir.x;
		else
			ray.distance_to_wall = (ray.y_map - player->pos.y + (1 - ray.step_y) / 2) / ray.dir.y;
		determine_wall_height(player, &ray);
		int j = ray.top_pixel;
		while (j < ray.bottom_pixel)
		{
			mlx_put_pixel(image, i, j, 0x00FF0000);
			j++;
		}
	}
}

