/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:56 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/19 13:51:46 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/cub3d.h"
#include "../inc/parse.h"
#include <stdio.h>

static void	setup_map(t_map **map, char *cub_file, mlx_t *mlx)
{
	*map = malloc(sizeof(t_map));
	if (!(*map))
	{
		mlx_close_window(mlx);
		exit_error(MALLOC_FAIL);
	}
	map_init(*map, cub_file, mlx);
	parse_cub(*map, cub_file);	
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*image;
	t_player	*player;

	if (argc != 2 || check_if_cub(argv[1]))
		exit_error(INCORRECT_NUM_ARG);
	create_window(&mlx, &image);
	setup_map(&map, argv[1], mlx);
	print_map(map);
	player_init(&player, mlx, image, map);
	raycasting(player);
	mlx_loop_hook(mlx, ft_hooks, player);
	mlx_loop(mlx);
	cleanup(map, player, mlx);
	return (0);
}
