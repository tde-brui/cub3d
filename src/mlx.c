/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:32:04 by sschelti          #+#    #+#             */
/*   Updated: 2023/12/06 16:38:52 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int	create_window(mlx_t **mlx)
{
	mlx_image_t	*image;

	*mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!(*mlx))
	{
		printf("%s\n", mlx_strerror(mlx_errno));
		exit (1);
	}
	image = mlx_new_image(*mlx, 128, 128);
	if (!image)
	{
		mlx_close_window(*mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (cleanup(NULL, *mlx, mlx_errno));
	}
	if (mlx_image_to_window(*mlx, image, 0, 0) == -1)
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
		player->y_pos += 0.03;
		raycasting(player);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_S))
	{
		player->y_pos -= 0.03;
		raycasting(player);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_D))
	{
		player->x_pos += 0.03;
		raycasting(player);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_A))
	{
		player->x_pos -= 0.03;
		raycasting(player);
	}
	// printf("x_pos: %f, y_pos: %f\n", player->x_pos, player->y_pos);
}
