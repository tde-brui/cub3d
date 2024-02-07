/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:45:52 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/07 16:47:18 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"
#include <stdio.h>

void	free_split(char **ptr)
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

void	parse_rgb(char *line, t_rgb *rgb)
{
	char	**split;

	split = ft_split(line, ',');
	rgb->r = ft_atoi(split[0]);
	rgb->g = ft_atoi(split[1]);
	rgb->b = ft_atoi(split[2]);
	free_split(split);
	rgb->colour = get_colour(rgb->r, rgb->g, rgb->b, 255);
}

void	parse_textures(char *line, t_texture *textures)
{
	char		**split;

	split = ft_split(line, ' ');
	printf("split[0]: %s\n", split[0]);
	printf("split[1]: %s\n", split[1]);
	if (!ft_strncmp("NO", split[0], 2))
		textures[NORTH].path = ft_strdup(split[1]);
	else if (!ft_strncmp("EA", split[0], 2))
		textures[EAST].path = ft_strdup(split[1]);
	else if (!ft_strncmp("SO", split[0], 2))
		textures[SOUTH].path = ft_strdup(split[1]);
	else if (!ft_strncmp("WE", split[0], 2))
		textures[WEST].path = ft_strdup(split[1]);
	else if (!ft_strncmp("F", split[0], 1))
		parse_rgb(split[1], textures[FLOOR].colour);
	else if (!ft_strncmp("C", split[0], 1))
		parse_rgb(split[1], textures[CEILING].colour);
	free_split(split);
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

t_map	*parse_cub(char *cub)
{
	t_map		*map;
	int			fd;
	char		*line;
	int			height;
	int			j;

	map_init(&map, cub);
	fd = open(cub, O_RDONLY);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		j = 0;
		if (check_if_texture_line(line))
			parse_textures(line, map->textures);
		else if (check_if_map_line(line))
		{
			parse_map(line, map, height, cub);
			height++;
		}
		free(line);
	}
	close(fd);
	convert_textures(map->textures);
	return (map);
}
