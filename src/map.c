/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:33:58 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/19 12:09:51 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"
#include <stdio.h>


static void	allocate_map_array(t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	map->map = malloc(sizeof(int *) * map->height);
	if (!map->map)
		cleanup_error(map, MALLOC_FAIL);
	while (i < map->height)
	{
		map->map[i] = malloc(sizeof(int) * map->width);
		if (!map->map[i])
		{
			//if allocation fails remove previously allocated memory
			while (j < i)
			{
				free(map->map[i]);
				//set it to NULL for a check later in the cleanup function
				map->map[i] = NULL;
				j++;	
			}
			cleanup_error(map, MALLOC_FAIL);
		}
		i++;
	}
}

static void	get_map_dimensions(t_map *map, char *cub_file)
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

static void	init_textures(t_map *map)
{
	unsigned int		i;

	i = 0;
	map->textures = malloc(sizeof(t_texture) * NUM_OF_TEXTURES);
	if (!map->textures)
		cleanup_error(map, MALLOC_FAIL);
	while (i != NUM_OF_TEXTURES)
	{
		map->textures[i].direction = i;
		map->textures[i].path = NULL;
		map->textures[i].texture_mlx = NULL;
		map->textures[i].colour = 0;
		i++;
	}
}

int	map_init(t_map *map, char *cub_file, mlx_t *mlx)
{
	//set mlx to mlx pointer for easy of use cleanup_error function
	map->mlx = mlx;
	//set textures and map to NULL so they can be freed without segfault in cleanup error
	map->textures = NULL;
	map->map = NULL;
	map->start_dir = '\0';
	//upon failure init_textures, only map struct will be freed.
	init_textures(map);
	//if there is a problem opening files call cleanup error, 
	//textures will now be freed since they have been allocated
	get_map_dimensions(map, cub_file);
	printf("max width: %d\n", map->width);
	printf("height: %d\n", map->height);
	allocate_map_array(map);
	return (0);
}

static int	determine_width(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

void	parse_map(char *first_line, int fd, t_map *map)
{
	int	j;
	int i;
	char *line;
	int	width;

	i = 0;
	line = first_line;
	while (line && check_if_map_line(line))
	{
		j = 0;
		width = determine_width(line);
		while (j < width && ft_isspace(line[j]))
		{
			map->map[i][j] = 0;
			j++;
		}
		while (j < width)
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
			j++;
		}
		while (j < map->width)
		{
			map->map[i][j] = 0;
			j++;
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
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


