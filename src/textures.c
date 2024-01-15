/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:28:33 by sschelti          #+#    #+#             */
/*   Updated: 2024/01/15 15:08:20 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	trim_newline(char **untrimmed)
{
	char			*trimmed;
	unsigned int	len_trimmed;

	len_trimmed = ft_strlen(*untrimmed) - 1;
	trimmed = ft_substr(*untrimmed, 0, len_trimmed);
	free (*untrimmed);
	*untrimmed = trimmed;
}

void    convert_textures(t_texture *textures)
{
    int i;

    i = 0;
    while (i != NUM_OF_TEXTURES - 2)
    {
        trim_newline(&(textures[i].path));
        textures[i].texture_mlx = mlx_load_png(textures[i].path);
        //fail check
        i++;
    }
}
