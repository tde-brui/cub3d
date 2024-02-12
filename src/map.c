/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:33:58 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/12 14:18:42 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include <stdio.h>

//(*map) = map_struct
static int	allocate_map_array(t_map **map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	(*map)->map = malloc(sizeof(int *) * (*map)->height);
	if (!(*map)->map)
		return (MALLOC_FAIL);
	while (i < (*map)->height)
	{
		(*map)->map[i] = malloc(sizeof(int) * (*map)->width);
		if (!(*map)->map[i])
		{
			while (j < i)
			{
				free((*map)->map[i]);
				(*map)->map[i] = NULL;
				j++;	
			}
			return (MALLOC_FAIL);
		}
		i++;
	}
	return (0);
}

static int	get_map_dimensions(t_map **map, char *cub_file)
{
	int	fd;

	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		return (FILE_ERROR);
	(*map)->height = get_max_height(fd);
	if (close(fd) == -1)
		return (FILE_ERROR);
	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		return (FILE_ERROR);
	(*map)->width = get_max_width(fd);
	if (close(fd) == -1)
		return (FILE_ERROR);
	return (0);
}

static int	init_textures(t_map *map)
{
	unsigned int		i;

	i = 0;
	map->textures = malloc(sizeof(t_texture) * NUM_OF_TEXTURES);
	if (!map->textures)
		return (MALLOC_FAIL);
	while (i != NUM_OF_TEXTURES)
	{
		map->textures[i].direction = i;
		map->textures[i].path = NULL;
		map->textures[i].texture_mlx = NULL;
		map->textures[i].colour = 0;
		i++;
	}
	return (0);
}

int	map_init(t_map **map, char *cub_file)
{
	unsigned int	ret_val;

	*map = malloc(sizeof(t_map));
	if (!(*map))
		return (MALLOC_FAIL);
	(*map)->textures = NULL;
	(*map)->map = NULL;
	ret_val = init_textures(*map);
	if (ret_val)
		return (ret_val);
	ret_val = get_map_dimensions(map, cub_file);
	if (ret_val)
		return (ret_val);
	printf("max width: %d\n", (*map)->width);
	printf("height: %d\n", (*map)->height);
	ret_val = allocate_map_array(map);
	if (ret_val)
		return (ret_val);
	return (0);
}

static int	determine_width(t_map *map, int i, char *line)
{
	return (ft_strlen(line) - 1);
}

void	parse_map(char *line, t_map *map, int i, char *cub)
{
	int	j;
	int	width;

	j = 0;
	printf("%s\n", line);
	width = determine_width(map, i, line);
	while (j < width)
	{
		if (line[j] == 'N' || line[j] == 'E'
			|| line[j] == 'S' || line[j] == 'W')
		{
			map->start_pos_x = j;
			map->start_pos_y = i;
			map->start_dir = line[j];
			map->map[i][j] = 0;
		}
		else if (line[j] == '1' || line[j] == '0')
			map->map[i][j] = line[j] - 48;
		else if (ft_isspace(line[j]))
			map->map[i][j] = 0;
		else
			exit_error(INVALID_CHAR_MAP);
		j++;
	}
	while (j < map->width)
	{
		map->map[i][j] = 0;
		j++;
	}
}

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%d ", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
