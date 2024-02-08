/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 13:45:21 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/08 12:59:49 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 512
# define HEIGHT 512
# include "../libs/mlx/include/MLX42/MLX42.h"
# include "../inc/parse.h"
# include "../libs/libft/libft.h"
# include <math.h>
# include "parse.h"
# include <stdio.h>

typedef struct player
{
	double		x_pos;
	double		y_pos;

	double		x_dir;
	double		y_dir;

	double		x_plane;
	double		y_plane;

	double		time;
	double		oldtime;

	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*image;

	uint32_t	screen_buffer[HEIGHT][WIDTH];

}	t_player;

typedef struct ray
{
	double		x_dir;
	double		y_dir;

	double		delta_dist_x;
	double		delta_dist_y;

	double		side_dist_x;
	double		side_dist_y;

	int			stepx;
	int			stepy;

	int			x_map;
	int			y_map;

	double		player_distance;

	int			side;

	int			wall_height;
	int			draw_start;
	int			draw_end;

	int			direction;
	int			texture_x;
	t_texture	*texture;
}	t_ray;

int			create_window(mlx_t **mlx, mlx_image_t **image);
t_player	*player_init(mlx_t *mlx, mlx_image_t *image, t_map *map);
void		ft_hooks(void *param);
int			cleanup(t_player *player, mlx_t *mlx, int errno);
void		raycasting(t_player *player);
void		calculate_delta_dist(t_ray *ray);
void		calculate_step_side_dist(t_player *player, t_ray *ray);
t_map		*parse_cub(char *cub);
uint32_t	get_colour(int r, int g, int b, int a);
void		rotate_player(double delta_angle, t_player *player);
void		move_player(double sign, t_player *player);
void		dda(t_player *player, t_ray *ray);
void		calculate_player_distance(t_ray *ray);
void		draw_wall(t_player *player, t_ray *ray, int x);
void		draw_background(t_player *player);
void		calculate_wall_height(t_ray *ray);
void		buffer_to_image(t_player *player);
void		calculate_texture_x(t_ray *ray, t_player *player);
int			select_texture(t_ray *ray);
void		strafe(double sign, t_player *player);
void		draw_background(t_player *player);

#endif