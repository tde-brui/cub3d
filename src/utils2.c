/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tde-brui <tde-brui@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/07 17:09:29 by tde-brui      #+#    #+#                 */
/*   Updated: 2024/02/16 17:26:37 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	exit_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	ft_free_map_copy(t_map *map_copy)
{
	int	i;

	i = 0;
	while (i < map_copy->height)
	{
		free(map_copy->map[i]);
		i++;
	}
	free(map_copy->map);
	free(map_copy);
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
