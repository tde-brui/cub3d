/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:59:31 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/16 18:21:02 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void	config_start_pos(t_map *map, int i, int j, char direction)
{
	if (!map->start_dir)
	{
		map->start_pos_x = j;
		map->start_pos_y = i;
		map->start_dir = direction;
		map->map[i][j] = 0;
	}
	else
		exit_error(MULTIPLE_START_POS);
}
