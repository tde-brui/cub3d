/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:40:12 by sschelti      #+#    #+#                 */
/*   Updated: 2023/12/21 18:57:15 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void init_ray(t_ray *ray, t_player *player, double camera)
{
	ray->dir.x = player->dir.x + player->plane.x * camera;
	ray->dir.y = player->dir.y + player->plane.y * camera;
	//printf("ray dir x: %f ray dir y: %f\n", ray->dir.x, ray->dir.y);
	ray->x_map = (int)player->pos.x;
	ray->y_map = (int)player->pos.y;
	if (ray->dir.x != 0)
		ray->delta_dist.x = sqrt(1 + (pow(ray->dir.y, 2) / pow(ray->dir.x, 2)));
	else
		ray->delta_dist.x = 1e30;
	if (ray->dir.y != 0)
		ray->delta_dist.y = sqrt(1 + (pow(ray->dir.x, 2) / pow(ray->dir.y, 2)));
	else
		ray->delta_dist.y = 1e30;
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
	while (ray->hit == 0 && ray->x_map < map->width && ray->y_map < map->height)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->x_map += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->y_map += ray->step_y;
			ray->side = 1;
		}
		if (map->map[ray->y_map][ray->x_map] != 0)
			ray->hit = 1;
	}
}

void draw_walls(t_ray *ray, t_player *player, mlx_image_t *image, int i)
{
	int		j;
	double	wall_height;
	double	wall_start;
	double	wall_end;

	wall_height = (int)(HEIGHT / ray->distance_to_wall);
	wall_start = -wall_height / 2 + HEIGHT / 2;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = wall_height / 2 + HEIGHT / 2;
	if (wall_end >= HEIGHT)
		wall_end = HEIGHT - 1;
	j = 0;
	while (j < wall_start)
	{
		mlx_put_pixel(image, i, j, 0x00000000);
		j++;
	}
	while (j < wall_end)
	{
		if (ray->side == 1)
		{
			mlx_put_pixel(image, i, j, 0xff0044);
		}
		else
		{
			mlx_put_pixel(image, i, j, 0x3c3248);
		}
		j++;
	}
	while (j < HEIGHT)
	{
		mlx_put_pixel(image, i, j, 0x00000000);
		j++;
	}
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
		init_ray(&ray, player, camera);
		determine_side_dist(player, &ray);
		dda(player, &ray, map);
		printf("ray side dist x: %f ray side dist y: %f\n", ray.side_dist.x, ray.side_dist.y);
		if (ray.side == 0)
			ray.distance_to_wall = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.distance_to_wall = (ray.side_dist.y - ray.delta_dist.y);
		//printf("ray distance to wall: %f\n", ray.distance_to_wall);
		draw_walls(&ray, player, image, i);
		i++;
	}
}

