/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:18:55 by sschelti          #+#    #+#             */
/*   Updated: 2024/02/08 16:05:15 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    png_error()
{
    printf("unable to open png\n");
    exit(1);
}

int	exit_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}
