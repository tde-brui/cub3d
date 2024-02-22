/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:45:52 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/22 14:53:49 by tde-brui      ########   odam.nl         */
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

int	valid_rgb_format(char *line)
{
	int	i;
	int	chars;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i] && commas < 3)
	{
		chars = 0;
		while (line[i] >= '0' && line[i] <= '9')
		{
			i++;
			chars++;
		}
		printf("chars: %d\n", chars);
		if (chars > 3 || chars < 1)
			return (1);
		if (line[i] != ',' && commas < 2)
			return (1);
		i++;
		commas++;
	}
	return (0);
}

//returns a pointer to the uint_32 on success, returns NULL on return
int	parse_rgb(char *line, uint32_t *colour)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	printf("checking rgb for line : %s\n", line);
	if (valid_rgb_format(line))
		return (INVALID_RGB);
	split = ft_split(line, ',');
	if (!split)
		return (1);
	r = ft_atoi(split[0]);
	if (r < 0 || r > 255)
		return (free_split(split), INVALID_RGB);
	g = ft_atoi(split[1]);
	if (g < 0 || g > 255)
		return (free_split(split), INVALID_RGB);
	b = ft_atoi(split[2]);
	if (b < 0 || b > 255)
		return (free_split(split), INVALID_RGB);
	free_split(split);
	*colour = get_colour(r, g, b, 255);
	return (0);
}

static int	parse_textures(char *line, t_texture *textures)
{
	char		**split;
	int			ret;

	ret = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (MALLOC_FAIL);
	if (split_length(split) != 2)
		return (free_split(split), INVALID_SPLIT);
	printf("amount in split: %d\n", split_length(split));
	printf("split[0]: %s\n", split[0]);
	printf("split[1]: %s\n", split[1]);
	ret = check_for_paths(split, textures);
	if (ret)
		return (free_split(split), ret);
	ret = check_rgbs(split, textures);
	if (ret)
		return (free_split(split), ret);
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
