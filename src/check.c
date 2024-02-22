/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:16:48 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/22 16:43:11 by sschelti         ###   ########.fr       */
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

int	check_if_cub(char *cub)
{
	int	i;

	i = 0;
	while (cub[i])
		i++;
	if (cub[i - 1] != 'b' || cub[i - 2] != 'u'
		|| cub[i - 3] != 'c' || cub[i - 4] != '.')
		return (1);
	return (0);
}

int	check_if_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	check_if_texture_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
		|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C')
		return (1);
	return (0);
}
