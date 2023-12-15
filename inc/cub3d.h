/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:45:21 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/12/15 15:40:12 by tde-brui      ########   odam.nl         */
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
# include <stdbool.h>
# include <stdlib.h>
# define FOV (M_PI / 3)

typedef struct Vector2d
{
	double y;
	double x;
}t_Vector2d;


typedef struct player
{
	t_Vector2d	pos;
	t_Vector2d	dir;
	t_Vector2d	plane;

	int		x_map;
	int		y_map;

	double	time;
	double	oldtime;
	
	mlx_t	*mlx;
}t_player;

typedef struct ray
{
	t_Vector2d dir;
	t_Vector2d delta_dist;
	t_Vector2d side_dist;

	double 	step_x;
	double 	step_y;

	int		x_map;
	int		y_map;

	int		hit;
	
	double distance_to_wall;
}t_ray;

int			create_window(mlx_t **mlx);
t_player	*player_init(mlx_t *mlx, t_map *map);
void		ft_hooks(void *param, t_map *map);
int			cleanup(t_player *player, mlx_t *mlx, int errno);
void 		raycasting(t_player *player, t_map *map);
void    	calculate_delta_dist(t_ray *ray);
void    	calculate_step_side_dist(t_player *player, t_ray *ray);
t_map	*parse_cub(char *cub);

#endif