/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sschelti <sschelti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 12:34:59 by sschelti      #+#    #+#                 */
/*   Updated: 2024/02/07 14:08:38 by tde-brui      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>

int	cleanup(t_player *player, mlx_t *mlx, int errno)
{
	free(player);
	mlx_terminate(mlx);
	return (errno);
}
