/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 17:09:29 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/17 16:07:29 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// int check_if_textures_initialized(t_map *map)
// {
// 	if (!map->path || !map->so_texture || !map->we_texture
// 		|| !map->ea_texture || !map->sprite_texture)
// 		return (1);
// 	return (0);
// }

void	ft_free_map_copy(t_map *map_copy)
{
	int	i;

	i = 0;
	while (i < map_copy->height)
	{
		free(map_copy->map[i]);
		i++;
	}
	free(map_copy->map);
	free(map_copy);
}

int	check_if_cub(char *cub)
{
	int	i;

	i = 0;
	while (cub[i])
		i++;
	if (cub[i - 1] != 'b' || cub[i - 2] != 'u'
		|| cub[i - 3] != 'c' || cub[i - 4] != '.')
		return (1);
	return (0);
}
