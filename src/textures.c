/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:28:33 by sschelti          #+#    #+#             */
/*   Updated: 2024/02/20 12:47:42 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"

void	trim_newline(char **untrimmed, t_map *map)
{
	char			*trimmed;
	unsigned int	len_trimmed;

	len_trimmed = ft_strlen(*untrimmed) - 1;
	trimmed = ft_substr(*untrimmed, 0, len_trimmed);
	if (!trimmed)
		cleanup_error(map, MALLOC_FAIL);
	free(*untrimmed);
	*untrimmed = trimmed;
}

//if tetxture is not there, user did not input texture, terminate program
//else check if last char is newline if so trim newline
void	convert_textures(t_texture *textures, t_map *map)
{
	int	i;

	i = 0;
	while (i != NUM_OF_TEXTURES - 2)
	{
		if (!textures[i].path)
			cleanup_error(map, PNG_FAIL);
		else if (textures[i].path[ft_strlen(textures[i].path) - 1] == '\n')
			trim_newline(&(textures[i].path), map);
		textures[i].texture_mlx = mlx_load_png(textures[i].path);
		if (!textures[i].texture_mlx)
			cleanup_error(map, PNG_FAIL);
		i++;
	}
}

int	select_texture(t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->y_dir > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
	else
	{
		if (ray->x_dir > 0)
			return (EAST);
		else
			return (WEST);
	}
}

// if side == 1 NORTH or SOUTH is hit
void	calculate_texture_x(t_ray *ray, t_player *player)
{
	double		wall_x;
	t_texture	*texture;

	wall_x = 0.0;
	texture = &player->map->textures[select_texture(ray)];
	if (ray->side == 1)
		wall_x = player->x_pos + ray->player_distance * ray->x_dir;
	else
		wall_x = player->y_pos + ray->player_distance * ray->y_dir;
	wall_x -= floor(wall_x);
	ray->texture_x = (int)(wall_x * (double)texture->texture_mlx->width);
}
