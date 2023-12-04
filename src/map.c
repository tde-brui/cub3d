/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 16:33:58 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/12/04 17:19:25 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	map_init(t_map *map, char *cub)
{
	int	i;

	i = 0;
	map = ft_malloc(sizeof(t_map));
	map->textures = ft_malloc(sizeof(t_textures));
	map->height = get_height(cub);
	map->width = get_width(cub);
	map->map = ft_malloc(sizeof(int *) * map->height);
	while (i < map->height)
	{
		map->map[i] = ft_malloc(sizeof(int) * map->width);
		i++;
	}
}

void	parse_map(char *line, t_map *map, int i)
{
	int	j;

	j = 0;
	while (j < map->width)
	{
		if (line[j] == 'N' || line[j] == 'E' || line[j] == 'S' || line[j] == 'W')
		{
			map->start_pos_x = j;
			map->start_pos_y = i;
			map->map[i][j] = 50;
		}
		else
			map->map[i][j] = ft_atoi(&line[j]);
		j++;
	}
}
