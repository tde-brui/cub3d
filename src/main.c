/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:56 by tde-brui          #+#    #+#             */
/*   Updated: 2023/12/13 17:34:10 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
  t_map   *map;
	t_player	*player;

	if (create_window(&mlx))
		return (mlx_errno);
  map = parse_cub(argv[1]);
	player = player_init(mlx);
	if (!player)
		return (cleanup(NULL, mlx, 1));
	raycasting(player);
	// mlx_loop_hook(mlx, ft_hooks, player);
	// mlx_loop(mlx);
	return (cleanup(player, mlx, 0));
}
  
void	print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%d ", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
