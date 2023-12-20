/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 15:32:04 by sschelti      #+#    #+#                 */
/*   Updated: 2023/12/20 18:12:24 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

mlx_image_t *create_window(mlx_t **mlx)
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
		return (NULL);
	}
	if (mlx_image_to_window(*mlx, image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		printf("%s\n", mlx_strerror(mlx_errno));
		return (NULL);
	}
	return (image);
}

void	ft_hooks(void *param, t_map *map)
{
	t_player	*player;
	mlx_t		*mlx;

	player = param;
	mlx = player->mlx;
	if(mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if(mlx_is_key_down(mlx, MLX_KEY_W))
	{
		player->pos.y += 0.03;
		//raycasting(player, map);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_S))
	{
		player->pos.y -= 0.03;
		//raycasting(player, map);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_D))
	{
		player->pos.x += 0.03;
		//raycasting(player, map);
	}
	if(mlx_is_key_down(mlx, MLX_KEY_A))
	{
		player->pos.x -= 0.03;
		//raycasting(player, map);
	}
	// printf("x_pos: %f, y_pos: %f\n", player->x_pos, player->y_pos);
}
