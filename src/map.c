/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:33:58 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/15 12:13:59 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"
#include <stdio.h>


static void	allocate_map_array(t_map **map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	(*map)->map = malloc(sizeof(int *) * (*map)->height);
	if (!(*map)->map)
		cleanup_error(map, MALLOC_FAIL);
	while (i < (*map)->height)
	{
		(*map)->map[i] = malloc(sizeof(int) * (*map)->width);
		if (!(*map)->map[i])
		{
			//if allocation fails remove previously allocated memory
			while (j < i)
			{
				free((*map)->map[i]);
				//set it to NULL for a check later in the cleanup function
				(*map)->map[i] = NULL;
				j++;	
			}
			cleanup_error(map, MALLOC_FAIL);
		}
		i++;
	}
}

static void	get_map_dimensions(t_map **map, char *cub_file)
{
	int	fd;

	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		cleanup_error(map, FILE_ERROR);
	(*map)->height = get_max_height(fd);
	if (close(fd) < 0)
		cleanup_error(map, FILE_ERROR);
	fd = open(cub_file, O_RDONLY);
	if (fd < 0)
		cleanup_error(map, FILE_ERROR);
	(*map)->width = get_max_width(fd);
	if (close(fd) < 0)
		cleanup_error(map, FILE_ERROR);
}

static void	init_textures(t_map **map)
{
	unsigned int		i;

	i = 0;
	(*map)->textures = malloc(sizeof(t_texture) * NUM_OF_TEXTURES);
	if (!(*map)->textures)
		cleanup_error(map, MALLOC_FAIL);
	while (i != NUM_OF_TEXTURES)
	{
		(*map)->textures[i].direction = i;
		(*map)->textures[i].path = NULL;
		(*map)->textures[i].texture_mlx = NULL;
		(*map)->textures[i].colour = 0;
		i++;
	}
}

int	map_init(t_map **map, char *cub_file, mlx_t **mlx)
{
	unsigned int	ret_val;

	//if fails, return error code and handle from there, 
	// cleanup function can't be called yet since map isn't allocated.
	*map = malloc(sizeof(t_map));
	if (!(*map))
		return (MALLOC_FAIL);
	//set mlx to mlx pointer for easy of use cleanup_error function
	(*map)->mlx = mlx;
	//set textures and map to NULL so they can be freed without segfault in cleanup error
	(*map)->textures = NULL;
	(*map)->map = NULL;
	//upon failure init_textures, only map struct will be freed.
	init_textures(map);
	//if there is a problem opening files call cleanup error, 
	//textures will now be freed since they have been allocated
	get_map_dimensions(map, cub_file);
	printf("max width: %d\n", (*map)->width);
	printf("height: %d\n", (*map)->height);
	allocate_map_array(map);
	return (0);
}

static int	determine_width(t_map *map, int i, char *line)
{
	return (ft_strlen(line) - 1);
}

void	parse_map(char *line, t_map **map, int i, char *cub)
{
	int	j;
	int	width;

	j = 0;
	printf("%s\n", line);
	width = determine_width((*map), i, line);
	while (j < width)
	{
		if (line[j] == 'N' || line[j] == 'E'
			|| line[j] == 'S' || line[j] == 'W')
		{
			(*map)->start_pos_x = j;
			(*map)->start_pos_y = i;
			(*map)->start_dir = line[j];
			(*map)->map[i][j] = 0;
		}
		else if (line[j] == '1' || line[j] == '0')
			(*map)->map[i][j] = line[j] - 48;
		else if (ft_isspace(line[j]))
			(*map)->map[i][j] = 0;
		else
			cleanup_error(map, INVALID_CHAR_MAP);
		j++;
	}
	while (j < (*map)->width)
	{
		(*map)->map[i][j] = 0;
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
