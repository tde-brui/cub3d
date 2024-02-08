/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 16:33:58 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/08 14:01:43 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include <stdio.h>

int	determine_width(t_map *map, int i, char *line)
{
	return (ft_strlen(line) - 1);
}

void	parse_map(char *line, t_map *map, int i, char *cub)
{
	int	j;
	int	width;

	j = 0;
	printf("%s\n", line);
	width = determine_width(map, i, line);
	while (j < width)
	{
		if (line[j] == 'N' || line[j] == 'E'
			|| line[j] == 'S' || line[j] == 'W')
			config_start_pos(map, i, j, line[j]);
		else if (line[j] == '1' || line[j] == '0')
			map->map[i][j] = line[j] - 48;
		else if (ft_isspace(line[j]))
			map->map[i][j] = 0;
		else
			exit_error("Error\nInvalid character in map\n");
		j++;
	}
	while (j < map->width)
	{
		map->map[i][j] = 0;
		j++;
	}
}

void	print_map(t_map *map)
{
	int	i;
	int	j;

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
