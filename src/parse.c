/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:45:52 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/16 00:07:22 by tijmendebru   ########   odam.nl         */
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

int isClosed(t_map *map, int row, int col)
{
	printf("map[%d][%d] : %d\n", row, col, map->map[row][col]);
	if (row < 0 || row >= map->height || col < 0 || col >= map->width)
		return (1);
	if (map->map[row][col] == 0)
		return (0);
	if (map->map[row][col] == 2)
		return (1);
	map->map[row][col] = 2;
	int result = 1;
	result &= isClosed(map, row + 1, col); 
	result &= isClosed(map, row - 1, col);
	result &= isClosed(map, row, col + 1);
	result &= isClosed(map, row, col - 1);
	return (result);
}

int check_if_closed(t_map *map)
{
	int i;

	i = 0;
	while (i < map->height)
	{
		if (map->map[i][0] == 0 && isClosed(map, i, 0))
			return (1);
		if (map->map[i][map->width - 1] == 0 && isClosed(map, i, map->width - 1))
			return (1);
		i++;
	}
	i = 0;
	while (i < map->width)
	{
		if (map->map[0][i] == 0 && isClosed(map, 0, i))
			return (1);
		if (map->map[map->height - 1][i] == 0 && isClosed(map, map->height - 1, i))
			return (1);
		i++;
	}
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
	if (check_if_closed(map) == 1)
		exit_error("Error\nMap is not closed\n");
	close(fd);
	convert_textures(map->textures);
	return (map);
}
