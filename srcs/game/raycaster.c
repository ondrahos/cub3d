/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:34:18 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 20:23:45 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

float	get_horizontal_inter(t_game_data *game_data, float angle)
{
	float	horizontal_x;
	float	horizontal_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	horizontal_y = floor(game_data->player->y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &horizontal_y, &y_step, 1);
	horizontal_x = game_data->player->x + (horizontal_y - game_data->player->y) \
		/ tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0) || \
		(!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(horizontal_x, horizontal_y - pixel, game_data))
	{
		horizontal_x += x_step;
		horizontal_y += y_step;
	}
	game_data->ray->horizontal_x = horizontal_x;
	game_data->ray->horizontal_y = horizontal_y;
	return (sqrt(pow(horizontal_x - game_data->player->x, 2) + \
	pow(horizontal_y - game_data->player->y, 2)));
}

float	get_vertical_inter(t_game_data *game_data, float angle)
{
	float	vertical_x;
	float	vertical_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	vertical_x = floor(game_data->player->x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &vertical_x, &x_step, 0);
	vertical_y = game_data->player->y
		+ (vertical_x - game_data->player->x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0) || \
	(!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(vertical_x - pixel, vertical_y, game_data))
	{
		vertical_x += x_step;
		vertical_y += y_step;
	}
	game_data->ray->vertical_x = vertical_x;
	game_data->ray->vertical_y = vertical_y;
	return (sqrt(pow(vertical_x - game_data->player->x, 2) + \
	pow(vertical_y - game_data->player->y, 2)));
}

void	cast_rays(t_game_data *game_data)
{
	double	horizontal_inter;
	double	vertical_inter;
	int		ray;

	ray = 0;
	game_data->ray->angle = game_data->player->angle
		- (game_data->player->fov_in_radians / 2);
	while (ray < WIN_WIDTH)
	{
		game_data->ray->flag = 0;
		horizontal_inter = get_horizontal_inter \
			(game_data, normalize_angle(game_data->ray->angle));
		vertical_inter = get_vertical_inter \
			(game_data, normalize_angle(game_data->ray->angle));
		if (vertical_inter <= horizontal_inter)
			game_data->ray->distance = vertical_inter;
		else
		{
			game_data->ray->distance = horizontal_inter;
			game_data->ray->flag = 1;
		}
		render_wall(game_data, ray++);
		game_data->ray->angle += (game_data->player->fov_in_radians
				/ WIN_WIDTH);
	}
}
