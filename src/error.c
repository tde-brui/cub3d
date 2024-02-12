/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:18:55 by sschelti          #+#    #+#             */
/*   Updated: 2024/02/12 14:10:36 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static const char	*cub3d_errors[CUB3D_ERRMAX] = {
	"Memory allocation failed",
	"Failed to load PNG",
	"Incorrect amount of arguments",
	"Invalid character in map",
	"Problem opening file",
};

void	exit_error(int error_code)
{
	const char	*errString;

	if (!error_code)
		return ;
	else if (error_code <= 16)
		errString = mlx_strerror(error_code);
	else
		errString = cub3d_errors[error_code - 17];
	printf("%s\n", errString);
	exit(error_code);
}

static void	cleanup_map_array(int ***map_ptr)
{
	int	**map;

	map = *map_ptr;
	
}

void	cleanup(t_map **map, mlx_t **mlx)
{
	t_map	*map_struct;

	map_struct = *map;
	if (map_struct)
	{
		free(map_struct->textures);
		if (map_struct->map && map_struct->map[0])
			cleanup_map_array(&map_struct->map);
		free(map_struct->map);
		free(map_struct);
	}
	mlx_close_window(*mlx);
}
