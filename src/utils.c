/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:35:44 by tde-brui          #+#    #+#             */
/*   Updated: 2024/01/12 16:33:37 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit(1);
	return (ptr);
}

int	get_height(char *file)
{
	int		fd;
	int		i;
	int		height;
	char	*line;

	fd = open(file, O_RDONLY);
	height = 0;
	while (1)
	{
		i = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[i] == ' ')
			i++;
		if (line[i] != '1')
			continue ;
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	get_max_width(char *file)
{
	int		fd;
	int		i;
	int		width;
	char	*line;

	fd = open(file, O_RDONLY);
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
			continue ;
		if (ft_strlen(line) - 1 > (size_t)width)
			width = ft_strlen(line) - 1;
		free(line);
	}
	close(fd);
	return (width);
}

uint32_t	get_colour(int r, int g, int b, int a )
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	trim_newline(char **untrimmed)
{
	char			*trimmed;
	unsigned int	len_trimmed;

	len_trimmed = ft_strlen(*untrimmed) - 1;
	trimmed = ft_substr(*untrimmed, 0, len_trimmed);
	free (*untrimmed);
	*untrimmed = trimmed;
}
