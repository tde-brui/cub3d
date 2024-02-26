/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:45:52 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/26 14:06:33 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"
#include <stdio.h>

static char	*trim_newline(char *line, t_map *map)
{
	char			*trimmed;
	unsigned int	trimmedlen;

	trimmedlen = ft_strlen(line) - 1;
	trimmed = ft_substr(line, 0, trimmedlen);
	if (!trimmed)
		cleanup_error(map, MALLOC_FAIL);
	return (trimmed);
}

static int	parse_textures(char *line, t_map *map)
{
	char		**split;
	int			ret;

	ret = 0;
	line = trim_newline(line, map);
	split = ft_split(line, ' ');
	if (!split)
		return (MALLOC_FAIL);
	if (split_length(split) < 2)
		return (free(line), free_split(split), INVALID_SPLIT);
	ret = check_for_paths(split, map->textures);
	if (ret)
		return (free(line), free_split(split), ret);
	ret = check_rgbs(split, map->textures);
	if (ret)
		return (free(line), free_split(split), ret);
	free(line);
	free_split(split);
	return (0);
}

void	check_map_errors(t_map *map, int fd, int err)
{
	if (err)
	{
		close(fd);
		cleanup_error(map, err);
	}
	else if (map->start_dir == '\0')
	{
		close(fd);
		cleanup_error(map, NO_START_DIR);
	}
	else if (flood_from_start(map))
	{
		close(fd);
		cleanup_error(map, MAP_NOT_CLOSED);
	}
	close(fd);
}

int	parse_cub(t_map *map, char *cub_file)
{
	int			fd;
	char		*line;
	int			err;

	fd = open(cub_file, O_RDONLY);
	err = 0;
	if (fd < 0)
		cleanup_error(map, FILE_ERROR);
	while (1 && !err)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_if_texture_line(map, line) && !err)
			err = parse_textures(line, map);
		else if (check_if_map_line(line) && !err)
		{
			parse_map(line, fd, map);
			break ;
		}
		free(line);
	}
	check_map_errors(map, fd, err);
	convert_textures(map->textures, map);
	return (0);
}
