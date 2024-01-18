/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:28:33 by sschelti          #+#    #+#             */
/*   Updated: 2024/01/17 12:19:32 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"

void	trim_newline(char **untrimmed)
{
	char			*trimmed;
	unsigned int	len_trimmed;

	len_trimmed = ft_strlen(*untrimmed) - 1;
	trimmed = ft_substr(*untrimmed, 0, len_trimmed);
	free (*untrimmed);
	*untrimmed = trimmed;
}

void    convert_textures(t_texture *textures)
{
    int i;

    i = 0;
    while (i != NUM_OF_TEXTURES - 2)
    {
        trim_newline(&(textures[i].path));
        textures[i].texture_mlx = mlx_load_png(textures[i].path);
        i++;
    }
}

int select_texture(t_ray *ray)
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
void    calculate_texture_x(t_ray *ray, t_player *player, t_texture *texture)
{
    double      wall_x;

    wall_x = 0.0;
    printf("ray direction: %d\n", ray->direction);
    if (ray->side == 1)
        wall_x = player->x_pos + ray->player_distance * ray->x_dir;
    else
        wall_x = player->y_pos + ray->player_distance * ray->y_dir;
    printf("wall_x: %f\n", wall_x);   
    wall_x -= floor(wall_x);
    ray->texture_x = (int)(wall_x * (double)texture->texture_mlx->width);
    printf("x pixel texture: %d\n", ray->texture_x);
}
