/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paths_check.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 16:16:48 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/22 14:51:18 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"

int	check_for_paths(char **split, t_texture *textures)
{
	if (!ft_strncmp("NO", split[0], 2))
	{
		textures[NORTH].path = ft_strdup(split[1]);
		if (!(textures[NORTH].path))
			return (1);
	}
	else if (!ft_strncmp("EA", split[0], 2))
	{
		textures[EAST].path = ft_strdup(split[1]);
		if (!(textures[EAST].path))
			return (1);
	}
	else if (!ft_strncmp("SO", split[0], 2))
	{
		textures[SOUTH].path = ft_strdup(split[1]);
		if (!(textures[SOUTH].path))
			return (1);
	}
	else if (!ft_strncmp("WE", split[0], 2))
	{
		textures[WEST].path = ft_strdup(split[1]);
		if (!(textures[WEST].path))
			return (1);
	}
	return (0);
}

int	check_rgbs(char **split, t_texture *textures)
{
	uint32_t	colour;
	int			ret;

	colour = 0;
	ret = 0;
	if (!ft_strncmp("F", split[0], 1))
	{
		ret = parse_rgb(split[1], &colour);
		if (ret)
			return (ret);
		textures[FLOOR].colour = colour;
	}
	else if (!ft_strncmp("C", split[0], 1))
	{
		ret = parse_rgb(split[1], &colour);
		if (ret)
			return (ret);
		textures[CEILING].colour = colour;
	}
	return (0);
}
