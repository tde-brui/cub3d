/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:45:52 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/19 17:30:25 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"
#include <stdio.h>

static void	free_split(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

//returns a pointer to the uint_32 on success, returns NULL on return
int	parse_rgb(char *line, uint32_t *colour)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ',');
	if (!split)
		return (1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	*colour = get_colour(r, g, b, 255);
	return (0);
}

static int	parse_textures(char *line, t_texture *textures)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!split)
		return (1);
	printf("split[0]: %s\n", split[0]);
	printf("split[1]: %s\n", split[1]);
	if (check_for_paths(split, textures))
		return (free_split(split), 1);
	else if (check_rgbs(split, textures))
		return (free_split(split), 1);
	free_split(split);
	return (0);
}

void	check_map_errors(t_map *map, int fd, int err)
{
	if (map->start_dir == '\0')
	{
		close(fd);
		cleanup_error(map, NO_START_DIR);
	}
	if (flood_from_start(map))
	{
		close(fd);
		cleanup_error(map, MAP_NOT_CLOSED);
	}
	close(fd);
	if (err)
		cleanup_error(map, MALLOC_FAIL);
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
		if (check_if_texture_line(line) && !err)
			err = parse_textures(line, map->textures);
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
