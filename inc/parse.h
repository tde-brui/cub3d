/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:08:21 by tde-brui          #+#    #+#             */
/*   Updated: 2024/01/15 14:43:34 by sschelti         ###   ########.fr       */
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
	int	r;
	int	g;
	int	b;
}t_rgb;


typedef struct Texture
{
	enum DIRECTION	direction;
	char 			*path;
	mlx_texture_t	*texture_mlx;
	t_rgb			*color;
}t_texture;

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
}t_map;


void	*ft_malloc(size_t size);
int		get_height(char *file);
int		get_max_width(char *file);
void	map_init(t_map **map, char *cub);
void	parse_map(char *line, t_map *map, int i, char *cub);
void	print_map(t_map *map);
void	convert_textures(t_texture *textures);
void	trim_newline(char **untrimmed);

#endif