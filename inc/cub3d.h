/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:45:21 by tde-brui          #+#    #+#             */
/*   Updated: 2023/12/08 17:36:42 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 512
# define HEIGHT 512
# include "../libs/mlx/include/MLX42/MLX42.h"
# include <math.h>
# include "parse.h"
# include <stdio.h>

typedef struct player
{
	double	x_pos;
	double	y_pos;

	int		x_map;
	int		y_map;
	
	double	x_dir;
	double	y_dir;

	double	x_plane;
	double	y_plane;

	double	time;
	double	oldtime;
	
	mlx_t	*mlx;
}t_player;

typedef struct ray
{
	double	x_dir;
	double	y_dir;

	double	delta_dist_x;
	double	delta_dist_y;

	double	side_dist_x;
	double	side_dist_y;

	
}t_ray;

int			create_window(mlx_t **mlx);
t_player	*player_init(mlx_t *mlx);
void		ft_hooks(void *param);
int			cleanup(t_player *player, mlx_t *mlx, int errno);
void		raycasting(t_player *player);
void    	calculate_delta_dist(t_ray *ray);
void    	calculate_step_side_dist(t_player *player, t_ray *ray);
t_map	*parse_cub(char *cub);

#endif