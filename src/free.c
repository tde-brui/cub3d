/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:58:38 by sschelti          #+#    #+#             */
/*   Updated: 2024/02/22 17:58:39 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	ft_free_map_copy(t_map *map_copy, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(map_copy->map[j]);
		j++;
	}
	free(map_copy->map);
	free(map_copy);
}

void	free_split(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
