/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:45:21 by tde-brui          #+#    #+#             */
/*   Updated: 2023/12/04 17:49:19 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 512
# define HEIGHT 512
# include "../libs/mlx/include/MLX42/MLX42.h"

typedef struct player
{
	double	x_pos;
	double	y_pos;

	double	x_dir;
	double	y_dir;

	double	x_plane;
	double	y_plane;
	
	mlx_t	*mlx;
}t_player;

typedef struct ray
{
	double	x_pos;
	double	y_pos;

	double	x_dir;
	double	y_dir;
}t_ray;

mlx_t		*create_window(void);
t_player	*player_init(mlx_t *mlx);
void		ft_hooks(void *param);

#endif