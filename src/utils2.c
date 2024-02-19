/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:09:29 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/19 18:02:29 by sschelti         ###   ########.fr       */
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

void	ft_free_map_copy(t_map *map_copy, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(map_copy->map[j]);
		j++;
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

int	split_length(char **split)
{
	int	i;

	while (split[i])
		i++;
	return (i);
}
