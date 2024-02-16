/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:35:44 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/16 17:54:55 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"

int	get_max_height(int fd)
{
	int		i;
	int		height;
	char	*line;

	height = 0;
	while (1)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[i] == ' ')
			i++;
		if (line[i] != '1' && line[i] != '0')
			continue ;
		height++;
		free(line);
	}
	return (height);
}

int	get_max_width(int fd)
{
	int		i;
	int		width;
	char	*line;

	width = 0;
	while (1)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[i] == ' ')
			i++;
		if (line[i] != '1')
		{
			free(line);
			continue ;
		}
		if (ft_strlen(line) - 1 > (size_t)width)
			width = ft_strlen(line) - 1;
		free(line);
	}
	return (width);
}

uint32_t	get_colour(int r, int g, int b, int a )
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
