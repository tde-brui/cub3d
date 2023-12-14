/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:08:21 by tde-brui          #+#    #+#             */
/*   Updated: 2023/12/14 20:05:58 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct rgb
{
	int	r;
	int	g;
	int	b;
}t_rgb;

typedef struct Textures
{
	char	*north;
	char	*east;
	char	*south;
	char	*west;
	t_rgb	*floor;
	t_rgb	*ceiling;
}t_textures;

typedef struct Map
{
	t_textures	*textures;
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

#endif