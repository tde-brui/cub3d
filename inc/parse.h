/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:08:21 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/17 14:23:20 by stijn            ###   ########.fr       */
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

enum DIRECTION
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
	enum DIRECTION	direction;
	char			*path;
	mlx_texture_t	*texture_mlx;
	uint32_t		colour;
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
int 	flood_from_start(t_map *map);
void	parse_map(char *line, t_map *map, int i, char *cub);
void	print_map(t_map *map);
void	convert_textures(t_texture *textures);
void	trim_newline(char **untrimmed);
int		ft_isspace(char c);
void	ft_free_map_copy(t_map *map_copy);
int		check_if_cub(char *cub);

#endif