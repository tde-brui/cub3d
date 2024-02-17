/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/04 16:35:44 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/17 15:58:34 by tijmendebru   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"

int	get_max_height(int fd)
{
	int		height;
	char	*line;

	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		while (check_if_map_line(line))
		{
			free(line);
			height++;
			line = get_next_line(fd);
			if (!line)
				return (height);
			if (!check_if_map_line(line))
			{
				free(line);
				return (height);
			}
		}
		free(line);
		line = get_next_line(fd);
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
