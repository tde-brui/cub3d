/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:18:55 by sschelti          #+#    #+#             */
/*   Updated: 2024/02/19 16:22:50 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static const char	*g_cub3d_errors[CUB3D_ERRMAX] = {
	"Memory allocation failed",
	"Failed o load PNG",
	"Incorrect amount of arguments",
	"Invalid character in map",
	"Problem opening file",
	"Multiple start position",
	"Map is not enclosed",
	"No start position",
	"Map not last item in file",
	"Input file is not a .cub file"
};

void	exit_error(int error_code)
{
	const char	*err_string;

	if (!error_code)
		return ;
	else if (error_code <= 16)
		err_string = mlx_strerror(error_code);
	else
		err_string = g_cub3d_errors[error_code - 17];
	printf("%s\n", err_string);
	exit(error_code);
}

static void	cleanup_map_array(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
}

static void	cleanup_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i != NUM_OF_TEXTURES)
	{
		if (map->textures[i].path)
			free(map->textures[i].path);
		if (map->textures[i].texture_mlx)
			mlx_delete_texture(map->textures[i].texture_mlx);
		i++;
	}
	free(map->textures);
}

// can only be called after map is allocated
void	cleanup_error(t_map *map, int error_code)
{
	if (map)
	{
		if (map->textures)
			cleanup_textures(map);
		if (map->map && map->map[0])
			cleanup_map_array(map);
		if (map->map)
			free(map->map);
		mlx_close_window(map->mlx);
		free(map);
	}
	exit_error(error_code);
}

//this function is only called at the end of the program
//everything is malloced nothing has failed
void	cleanup(t_map *map, t_player *player, mlx_t *mlx)
{
	free(player);
	cleanup_textures(map);
	cleanup_map_array(map);
	free(map->map);
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	free(map);
	exit(0);
}
