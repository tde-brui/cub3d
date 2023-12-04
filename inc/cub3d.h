/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:45:21 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/12/04 16:52:42 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 512
# define HEIGHT 512
# include "parse.h"
# include <stdio.h>

typedef struct player
{
	double	x_pos;
	double	y_pos;

	double	x_dir;
	double	y_dir;

	double	x_plane;
	double	y_plane;
}t_player;

typedef struct ray
{
	double	x_pos;
	double	y_pos;

	double	x_dir;
	double	y_dir;
}t_ray;

void    create_window();
t_map	*parse_cub(char *cub);

#endif