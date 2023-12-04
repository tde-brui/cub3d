/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:50:56 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/12/04 17:14:44 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libs/mlx/include/MLX42/MLX42.h"
#include "../inc/cub3d.h"
#include <stdio.h>

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%d,", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
int	main(int argc, char **argv)
{
	t_map	*map;

	create_window();
	map = parse_cub(argv[1]);
	printf("map height %d\n", map->height);
	//print_map(map);
	return (1);
}
