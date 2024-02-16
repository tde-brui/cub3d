/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: stijn <stijn@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 14:08:21 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/16 17:26:54 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define NUM_OF_TEXTURES 6

# include <stdlib.h>
# include "../libs/libft/libft.h"
# include "../libs/mlx/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>

enum DIRECTION
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING
};

typedef struct rgb
{
	int			r;
	int			g;
	int			b;
	uint32_t	colour;
}	t_rgb;


typedef struct Texture
{
	enum DIRECTION	direction;
	char			*path;
	mlx_texture_t	*texture_mlx;
	t_rgb			*colour;
}	t_texture;

//textures is an array for the 6 textures
typedef struct Map
{
	t_texture	*textures;
	int			**map;
	int			width;
	int			height;
	int			start_pos_x;
	int			start_pos_y;
	char		start_dir;
}	t_map;


void	map_init(t_map **map, char *cub);
void	config_start_pos(t_map *map, int i, int j, char direction);

void	*ft_malloc(size_t size);
int		get_height(char *file);
int		get_max_width(char *file);
int 	flood_from_start(t_map *map);
void	parse_map(char *line, t_map *map, int i, char *cub);
void	print_map(t_map *map);
void	convert_textures(t_texture *textures);
void	trim_newline(char **untrimmed);
int		exit_error(char *str);
int		ft_isspace(char c);
void	ft_free_map_copy(t_map *map_copy);
int		check_if_cub(char *cub);

#endif