/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:33:58 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/22 16:47:05 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"
#include <stdio.h>

static int	determine_width(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

void	config_map(t_map *map, int j, int i, char *line)
{
	if (line[j] == 'N' || line[j] == 'E'
		|| line[j] == 'S' || line[j] == 'W')
		config_start_pos(map, i, j, line[j]);
	else if (line[j] == '1' || line[j] == '0')
		map->map[i][j] = line[j] - 48;
	else if (ft_isspace(line[j]))
		map->map[i][j] = 0;
	else
		cleanup_error(map, INVALID_CHAR_MAP);
}

void	check_after_map(char *line, int fd, t_map *map)
{
	while (line)
	{
		if (check_if_map_line(line))
			cleanup_error(map, MAP_NOT_LAST);
		if (check_if_texture_line(line))
			cleanup_error(map, MAP_NOT_LAST);
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_map(char *first_line, int fd, t_map *map)
{
	int		j;
	int		i;
	char	*line;
	int		width;

	i = 0;
	line = first_line;
	while (line && check_if_map_line(line))
	{
		j = 0;
		width = determine_width(line);
		while (j < width && ft_isspace(line[j]))
			map->map[i][j++] = 0;
		while (j < width)
			config_map(map, j++, i, line);
		while (j < map->width)
			map->map[i][j++] = 0;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	check_after_map(line, fd, map);
}
