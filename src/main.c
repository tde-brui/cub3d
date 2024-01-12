/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:56 by tde-brui          #+#    #+#             */
/*   Updated: 2024/01/12 15:54:23 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/cub3d.h"
#include "../inc/parse.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
  	t_map   	*map;
	mlx_image_t	*image;
	t_player	*player;

	if (argc != 2)
		return (1);
	if (create_window(&mlx, &image))
		return (mlx_errno);
  	map = parse_cub(argv[1]);
	print_map(map);
	player = player_init(mlx, image, map);
	if (!player)
		return (cleanup(NULL, mlx, 1));
	raycasting(player);
	mlx_loop_hook(mlx, ft_hooks, player);
	mlx_loop(mlx);
	return (cleanup(player, mlx, 0));
}

