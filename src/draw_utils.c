/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stijn <stijn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:33:08 by tde-brui          #+#    #+#             */
/*   Updated: 2024/02/12 12:10:07 by stijn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_ceiling(t_player *player, uint32_t ceiling_colour)
{
	int y;
	int x;

	y = 0;
	while (y != HEIGHT / 2)
	{
		x = 0;
		while (x != WIDTH)
		{
			player->screen_buffer[y][x] = ceiling_colour;
			x++;
		}
		y++;
	}

}

void	draw_floor(t_player *player, uint32_t floor_colour)
{
	int	y;
	int	x;

	y = HEIGHT / 2;
	while (y != HEIGHT)
	{
		x = 0;
		while (x != WIDTH)
		{
			player->screen_buffer[y][x] = floor_colour;
			x++;
		}
		y++;
	}
}
void	draw_background(t_player *player)
{
	uint32_t	*ceiling_colour;
	uint32_t	*floor_colour;

	ceiling_colour = player->map->textures[CEILING].colour;
	floor_colour = player->map->textures[FLOOR].colour;
	draw_ceiling(player, ceiling_colour);
	draw_floor(player, floor_colour);
}