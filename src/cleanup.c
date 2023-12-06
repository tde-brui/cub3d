/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:34:59 by sschelti          #+#    #+#             */
/*   Updated: 2023/12/06 15:00:05 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>

int    cleanup(t_player *player, mlx_t *mlx, int errno)
{
    free(player);
    mlx_terminate(mlx);
    return (errno);
}
