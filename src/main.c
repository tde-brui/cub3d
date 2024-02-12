/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:56 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/12 14:17:17 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/cub3d.h"
#include "../inc/parse.h"
#include <stdio.h>

static void	setup_map(t_map **map, char *cub_file, mlx_t **mlx)
{
	unsigned int	ret_val;

	ret_val = map_init(map, cub_file);
	if (ret_val)
	{
		cleanup(map, mlx);
		exit_error(ret_val);
	}
	
	// ret_val = map_alloc(map, cub_file);
	
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
	t_player	*player;

	if (argc != 2)
		exit_error(INCORRECT_NUM_ARG);
	create_window(&mlx, &image);
	setup_map(&map, argv[1], &mlx);
	return (0);
	map = parse_cub(argv[1]);
	print_map(map);
	player = player_init(mlx, image, map);
	// if (!player)
	// 	return ();
	raycasting(player);
	mlx_loop_hook(mlx, ft_hooks, player);
	mlx_loop(mlx);
	return (0);
}
