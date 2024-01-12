/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: stijn <stijn@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 15:32:04 by sschelti      #+#    #+#                 */
/*   Updated: 2024/01/12 16:45:41 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int	create_window(mlx_t **mlx, mlx_image_t **image)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!(*mlx))
	{
		printf("%s\n", mlx_strerror(mlx_errno));
		exit (1);
	}
	*image = mlx_new_image(*mlx, 512, 512);
	if (!(*image))
	{
		mlx_close_window(*mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (cleanup(NULL, *mlx, mlx_errno));
	}
	if (mlx_image_to_window(*mlx, *image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (cleanup(NULL, *mlx, mlx_errno));
	}
	return (0);
}

void	ft_hooks(void *param)
{
	t_player	*player;
	mlx_t		*mlx;

	player = param;
	mlx = player->mlx;
	if(mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if(mlx_is_key_down(mlx, MLX_KEY_W))
	{
		move_player(1.0, player);
		raycasting(player);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_S))
	{
		move_player(-1.0, player);
		raycasting(player);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		rotate_player(0.02, player);
		raycasting(player);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		rotate_player(-0.02, player);
		raycasting(player);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_A))
	{
		strafe(-1.0, player);
		raycasting(player);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_D))
	{
		strafe(1.0, player);
		raycasting(player);
	}
	// printf("x_pos: %f, y_pos: %f\n", player->x_pos, player->y_pos);
}
