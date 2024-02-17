/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:45:52 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/17 14:55:35 by stijn            ###   ########.fr       */
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

//split still needs to be checked for failure
static uint32_t	parse_rgb(char *line)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ',');
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	return (get_colour(r, g, b, 255));
}

static int	parse_textures(char *line, t_texture *textures)
{
	char		**split;

	split = ft_split(line, ' ');
	if (!split)
		return (1);
	printf("split[0]: %s\n", split[0]);
	printf("split[1]: %s\n", split[1]);
	if (!ft_strncmp("NO", split[0], 2))
	{
		textures[NORTH].path = ft_strdup(split[1]);
		if (!(textures[NORTH].path))
			return (1);
	}
	else if (!ft_strncmp("EA", split[0], 2))
	{
		textures[EAST].path = ft_strdup(split[1]);
		if (!(textures[EAST].path))
			return (1);
	}
	else if (!ft_strncmp("SO", split[0], 2))
	{
		textures[SOUTH].path = ft_strdup(split[1]);
		if (!(textures[SOUTH].path))
			return (1);
	}
	else if (!ft_strncmp("WE", split[0], 2))
	{
		textures[WEST].path = ft_strdup(split[1]);
		if (!(textures[WEST].path))
			return (1);
	}
	else if (!ft_strncmp("F", split[0], 1))
		textures[FLOOR].colour = parse_rgb(split[1]);
	else if (!ft_strncmp("C", split[0], 1))
		textures[CEILING].colour = parse_rgb(split[1]);
	free_split(split);
	return (0);
}

int	check_if_texture_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
		return (1);
	return (0);
}

int	check_if_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	parse_cub(t_map *map, char *cub_file)
{
	int			fd;
	char		*line;
	int			height;
	int			err;
	
	fd = open(cub_file, O_RDONLY);
	err = 0;
	if (fd < 0)
		cleanup_error(map, FILE_ERROR);
	height = 0;
	while (1 && !err)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_if_texture_line(line) && !err)
			err = parse_textures(line, map->textures);
		else if (check_if_map_line(line) && !err)
		{
			//parse_map cals cleanup function itself
			parse_map(line, map, height, cub_file);
			height++;
		}
		free(line);
	}
	if (flood_from_start(map))
		cleanup_error(map, MAP_NOT_CLOSED);
	close(fd);
	if (err)
		cleanup_error(map, MALLOC_FAIL);
	convert_textures(map->textures);
	return (0);
}
