/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sschelti <sschelti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:01:35 by tde-brui          #+#    #+#             */
/*   Updated: 2023/10/02 17:23:22 by sschelti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = ft_strlen(src);
	if (!dest)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	if (size > ft_strlen(src))
	{
		while (src[++i])
			dest[i] = src[i];
	}
	else
	{
		while (src[++i] && i < size - 1)
			dest[i] = src[i];
	}
	dest[i] = '\0';
	return (j);
}
