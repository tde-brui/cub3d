/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:50:56 by tde-brui          #+#    #+#             */
/*   Updated: 2023/12/04 17:50:20 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_player	*player;

	mlx = create_window();
	player = player_init(mlx);
	mlx_loop_hook(mlx, ft_hooks, player);
	mlx_loop(mlx);
	return (1);
}


