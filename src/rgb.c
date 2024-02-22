/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:59:45 by sschelti          #+#    #+#             */
/*   Updated: 2024/02/22 18:08:53 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"
#include "../inc/cub3d.h"

static int	check_rgb_value(char *value)
{
	int	len;

	len = 0;
	while (*value != '\0' && *value != ',' && *value != '\n')
	{
		if (*value < '0' || *value > '9')
			return (-1);
		len++;
		value++;
	}
	if (len > 0 && len < 4)
		return (len);
	else
		return (-1);
}

static int	valid_rgb_format(char *line)
{
	int	i;
	int	temp;
	int	value;

	i = 0;
	temp = 0;
	value = 0;
	while (value < 3)
	{
		temp = check_rgb_value(&line[i]);
		if (temp == -1)
			return (1);
		i += temp;
		if (line[i] == ',')
			value++;
		else if (value == 2 && (line[i] == '\0' || line[i] == '\n'))
			return (0);
		else
			return (1);
		i++;
	}
	return (1);
}

int	parse_rgb(char *line, uint32_t *colour)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	if (valid_rgb_format(line))
		return (INVALID_RGB);
	split = ft_split(line, ',');
	if (!split)
		return (1);
	r = ft_atoi(split[0]);
	if (r < 0 || r > 255)
		return (free_split(split), INVALID_RGB);
	g = ft_atoi(split[1]);
	if (g < 0 || g > 255)
		return (free_split(split), INVALID_RGB);
	b = ft_atoi(split[2]);
	if (b < 0 || b > 255)
		return (free_split(split), INVALID_RGB);
	free_split(split);
	*colour = get_colour(r, g, b, 255);
	return (0);
}
