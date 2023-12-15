/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:40:12 by sschelti      #+#    #+#                 */
/*   Updated: 2023/12/15 18:19:51 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_ray(t_player *player, t_ray *ray, double cameraX)
{
	ray->dir.x = player->dir.x + player->plane.x * cameraX;
	ray->dir.y = player->dir.y + player->plane.y * cameraX;
	if (ray->dir.x == 0)
		ray->dir.x = 1e30;
	if (ray->dir.y == 0)
		ray->dir.y = 1e30;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
}

void	determine_side_dist(t_player *player, t_ray *ray)
{
	if (ray->delta_dist.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (player->pos.x - player->x_map) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (player->x_map + 1 - player->pos.x) * ray->delta_dist.x;
	}
	if (ray->delta_dist.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (player->pos.y - player->y_map) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (player->y_map + 1 - player->pos.y) * ray->delta_dist.y;
	}
}

void	dda(t_player *player, t_ray *ray, t_map *map)
{
	printf("side dist x: %f\nside dist y: %f\n", ray->side_dist.x, ray->side_dist.y);
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			printf("%f\n", ray->side_dist.x);
			player->x_map += ray->step_x;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			printf("%f\n", ray->side_dist.y);
			player->y_map += ray->step_y;
		}
		if (map->map[player->y_map][player->x_map] != '0')
		{
			ray->hit = 1;
		}
	}
}

void	raycasting(t_player *player, t_map *map)
{
	int		i;
	double	cameraX;
	t_ray	*ray;

	ray = ft_malloc(sizeof(t_ray));
	i = 0;
	while (i < WIDTH)
	{
		printf("ray %d\n", i);
		cameraX = 2 * i / (double)WIDTH - 1;
		init_ray(player, ray, cameraX);
		determine_side_dist(player, ray);
		dda(player, ray, map);
		ray->distance_to_wall = sqrt(pow(player->pos.x - player->x_map, 2) + pow(player->pos.y - player->y_map, 2));
		i++;
    }
	free(ray);
}

