/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:08:21 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/22 17:56:22 by sschelti         ###   ########.fr       */
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
# include "error.h"

enum e_DIRECTION
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING
};

typedef struct Texture
{
	enum e_DIRECTION	direction;
	char				*path;
	mlx_texture_t		*texture_mlx;
	uint32_t			colour;
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
	mlx_t		*mlx;
}	t_map;

int		map_init(t_map *map, char *cub_file, mlx_t *mlx);
void	config_start_pos(t_map *map, int i, int j, char direction);
void	*ft_malloc(size_t size);
int		get_max_height(int fd);
int		get_max_width(int fd);
int		flood_from_start(t_map *map);
void	parse_map(char *first_line, int fd, t_map *map);
int		check_if_map_line(char *line);
void	print_map(t_map *map);
void	convert_textures(t_texture *textures, t_map *map);
int		ft_isspace(char c);
void	ft_free_map_copy(t_map *map_copy, int i);
int		check_if_cub(char *cub);
int		check_if_texture_line(char *line);
void	get_map_dimensions(t_map *map, char *cub_file);
int		check_for_paths(char **split, t_texture *textures);
int		check_rgbs(char **split, t_texture *textures);
int		parse_rgb(char *line, uint32_t *colour);
int		split_length(char **split);
void	free_split(char **ptr);

#endif