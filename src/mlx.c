/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:32:04 by sschelti          #+#    #+#             */
/*   Updated: 2023/12/04 17:51:29 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

mlx_t	*create_window(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 1);
	if (!mlx)
	{
		printf("%s\n", mlx_strerror(mlx_errno));
		exit (1);
	}
	image = mlx_new_image(mlx, 128, 128);
	if (!image)
	{
		mlx_close_window(mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		exit (1);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		exit (1);
	}
	return (mlx);
}

void	ft_hooks(void *param)
{
	t_player	*player;
	mlx_t		*mlx;

	player = param;
	mlx = player->mlx;
	if(mlx_is_key_down(mlx, MLX_KEY_W))
		;
}
