/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 14:08:21 by tde-brui      #+#    #+#                 */
/*   Updated: 2023/12/04 15:07:48 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include "libft/libft.h"

typedef struct Textures
{
	char	*north;
	char	*east;
	char	*south;
	char	*west;
	char	*floor;
	char	*ceiling;
}t_textures;

typedef struct Map
{
	t_textures	*textures;
	char		**map;
	int			width;
	int			height;
	int			start_pos;
	char		start_dir;
}t_map;

#endif