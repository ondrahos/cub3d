/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:53:04 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 20:26:59 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_game_data *game_data, int x, int y, int color)
{
	if (x < 0 || y < 0)
		return ;
	else if (x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	mlx_put_pixel(game_data->img, x, y, color);
}

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

int	wall_hit(float x, float y, t_game_data *game_data)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= game_data->data->map_height
			|| x_m >= game_data->data->map_width))
		return (0);
	if (game_data->data->map[y_m] && x_m
		<= (int)ft_strlen(game_data->data->map[y_m]))
		if (game_data->data->map[y_m][x_m] == '1')
			return (0);
	return (1);
}
