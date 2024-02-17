/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: stijn <stijn@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 15:18:55 by sschelti      #+#    #+#                 */
/*   Updated: 2024/02/17 16:46:55 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static const char	*cub3d_errors[CUB3D_ERRMAX] = {
	"Memory allocation failed",
	"Failed o load PNG",
	"Incorrect amount of arguments",
	"Invalid character in map",
	"Problem opening file",
	"Multiple start position",
	"Map is not enclosed",
	"No start position",
	"Map not last item in file"
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

static void	cleanup_map_array(t_map **map)
{
	int	i;

	i = 0;
	while (i < (*map)->height)
	{
		free((*map)->map[i]);
		i++;
	}
}

//path is either NULL or allocated can be freed either way. Same goes for textures pointer.
static void	cleanup_textures(t_map **map)
{
	int	i;

	i = 0;
	while (i != NUM_OF_TEXTURES)
	{
		if ((*map)->textures[i].path)
			free((*map)->textures[i].path);
		if ((*map)->textures[i].texture_mlx)
			free ((*map)->textures[i].texture_mlx);
		i++;
	}
	free((*map)->textures);
}

// can only be called after map is allocated
void	cleanup_error(t_map **map, int error_code)
{
	t_map	*map_struct;

	map_struct = *map;
	if (map_struct)
	{	
		if (map_struct->textures)
			cleanup_textures(map);
		//if the first item of map array = NULL, memory allocation failed and all the memory is already freed
		if (map_struct->map && map_struct->map[0])
			cleanup_map_array(map);
		if (map_struct->map)
			free(map_struct->map);
		mlx_close_window(*(map_struct->mlx));
		free(map_struct);
	}
	exit_error(error_code);
}

//this function is only called at the end of the program
//everything is malloced nothing has failed
void	cleanup(t_map **map, t_player **player, mlx_t *mlx)
{
	free(*player);
	cleanup_textures(map);
	cleanup_map_array(map);
	free((*map)->map);
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	free(*map);
	exit(0);
}
