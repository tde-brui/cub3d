/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:58:48 by sschelti          #+#    #+#             */
/*   Updated: 2024/02/22 17:58:49 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"

void	get_map_dimensions(t_map *map, char *cub_file)
{
	int	fd;

	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		cleanup_error(map, FILE_ERROR);
	map->height = get_max_height(fd);
	if (close(fd) < 0)
		cleanup_error(map, FILE_ERROR);
	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		cleanup_error(map, FILE_ERROR);
	map->width = get_max_width(fd);
	if (close(fd) < 0)
		cleanup_error(map, FILE_ERROR);
}

int	get_max_height(int fd)
{
	int		height;
	char	*line;

	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		while (check_if_map_line(line))
		{
			free(line);
			height++;
			line = get_next_line(fd);
			if (!line)
				return (height);
			if (!check_if_map_line(line))
			{
				free(line);
				return (height);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	return (height);
}

int	get_max_width(int fd)
{
	int		i;
	int		width;
	char	*line;

	width = 0;
	while (1)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[i] == ' ')
			i++;
		if (line[i] != '1')
		{
			free(line);
			continue ;
		}
		if (ft_strlen(line) - 1 > (size_t)width)
			width = ft_strlen(line) - 1;
		free(line);
	}
	return (width);
}
