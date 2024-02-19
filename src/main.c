/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: stijn <stijn@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:50:56 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/19 14:54:36 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/cub3d.h"
#include "../inc/parse.h"
#include <stdio.h>

static void	allocate_map_array(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	map->map = malloc(sizeof(int *) * map->height);
	if (!map->map)
		cleanup_error(map, MALLOC_FAIL);
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(int) * map->width);
		if (!map->map[i])
		{
			while (j < i)
			{
				free(map->map[i]);
				map->map[i] = NULL;
				j++;
			}
			cleanup_error(map, MALLOC_FAIL);
		}
		i++;
	}
}

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

	if (argc != 2)
		exit_error(INCORRECT_NUM_ARG);
	if (check_if_cub(argv[1]))
		exit_error(NOT_CUB_FILE);
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
