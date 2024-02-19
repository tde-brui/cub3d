/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 17:32:17 by stijn         #+#    #+#                 */
/*   Updated: 2024/02/19 15:14:14 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//rotates player using a angle between 0 and 2 * PI.
//to do: rotate camera plane and direction vector with 
//same angle using rotation matrix

void	rotate_player(double delta_angle, t_player *player)
{
	double	x_p;
	double	y_p;
	double	x_d;
	double	y_d;

	x_p = player->x_plane;
	y_p = player->y_plane;
	x_d = player->x_dir;
	y_d = player->y_dir;
	player->x_plane = x_p * cos(delta_angle) - y_p * sin(delta_angle);
	player->y_plane = x_p * sin(delta_angle) + y_p * cos(delta_angle);
	player->x_dir = x_d * cos(delta_angle) - y_d * sin(delta_angle);
	player->y_dir = x_d * sin(delta_angle) + y_d * cos(delta_angle);
	raycasting(player);
}

void	move_player(double sign, t_player *player)
{
	int	tempx;
	int	tempy;
	int	curr_x;
	int	curr_y;

	tempx = player->x_pos + player->x_dir * 0.02 * sign;
	tempy = player->y_pos + player->y_dir * 0.02 * sign;
	curr_x = (int)player->x_pos;
	curr_y = (int)player->y_pos;
	if (!player->map->map[tempy][tempx])
	{
		player->x_pos += player->x_dir * 0.02 * sign;
		player->y_pos += player->y_dir * 0.02 * sign;
	}
	else if (!player->map->map[tempy][curr_x])
		player->y_pos += player->y_dir * 0.02 * sign;
	else if (!player->map->map[curr_y][tempx])
		player->x_pos += player->x_dir * 0.02 * sign;
	raycasting(player);
}

void	strafe(double sign, t_player *player)
{
	int	curr_x;
	int	curr_y;
	int	tempx;
	int	tempy;

	tempx = player->x_pos + player->x_plane * 0.03 * sign;
	tempy = player->y_pos + player->y_plane * 0.03 * sign;
	curr_x = (int)player->x_pos;
	curr_y = (int)player->y_pos;
	if (!player->map->map[tempy][tempx])
	{
		player->x_pos += player->x_plane * 0.03 * sign;
		player->y_pos += player->y_plane * 0.03 * sign;
	}
	else if (!player->map->map[tempy][curr_x])
		player->y_pos += player->y_plane * 0.03 * sign;
	else if (!player->map->map[curr_y][tempx])
		player->x_pos += player->x_plane * 0.03 * sign;
	raycasting(player);
}
