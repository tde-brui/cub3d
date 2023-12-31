/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:45:52 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/12/06 16:39:37 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
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
}

void	parse_textures(char *line, t_textures *textures)
{
	char		**split;

	split = ft_split(line, ' ');
	printf("split[0]: %s\n", split[0]);
	printf("split[1]: %s\n", split[1]);
	if (!ft_strncmp("NO", split[0], 2))
		textures->north = ft_strdup(split[1]);
	else if (ft_strncmp("EA", split[0], 2))
		textures->east = ft_strdup(split[1]);
	else if (ft_strncmp("SO", split[0], 2))
		textures->south = ft_strdup(split[1]);
	else if (ft_strncmp("WE", split[0], 2))
		textures->west = ft_strdup(split[1]);
	else if (ft_strncmp("F", split[0], 1))
		parse_rgb(split[1], textures->floor);
	else if (ft_strncmp("C", split[0], 1))
		parse_rgb(split[1], textures->ceiling);
	free_split(split);
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
		while (line[j] == ' ')
			j++;
		if (line[j] != '1')
			parse_textures(line, map->textures);
		else if (line[j] == '1')
		{
			parse_map(line, map, height, cub);
			height++;
		}
		free(line);
	}
	close(fd);
	return (map);
}
