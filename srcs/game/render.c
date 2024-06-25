/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:43:33 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 20:26:17 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_floor_ceiling(t_game_data *game_data,
	int ray, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < WIN_HEIGHT)
		my_mlx_pixel_put(game_data, ray, i++, game_data->texture->floor_color);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game_data, ray, i++,
			game_data->texture->ceiling_color);
}

mlx_texture_t	*get_texture(t_game_data *game_data, int flag)
{
	game_data->ray->angle = normalize_angle(game_data->ray->angle);
	if (flag == 0)
	{
		if (game_data->ray->angle > PI
			/ 2 && game_data->ray->angle < 3 * (PI / 2))
			return (game_data->texture->east);
		else
			return (game_data->texture->west);
	}
	else
	{
		if (game_data->ray->angle > 0 && game_data->ray->angle < PI)
			return (game_data->texture->south);
		else
			return (game_data->texture->north);
	}
}

double	get_x_o(mlx_texture_t *texture, t_game_data *game_data)
{
	double	x_o;

	if (game_data->ray->flag == 1)
		x_o = (int)fmodf((game_data->ray->horizontal_x * \
		(texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((game_data->ray->vertical_y * \
		(texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}

void	draw_wall(t_game_data *game_data, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(game_data, game_data->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, game_data);
	y_o = (t_pix - (WIN_HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(game_data, game_data->ray->index, t_pix, reverse_bytes \
		(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	render_wall(t_game_data *game_data, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game_data->ray->distance *= cos(normalize_angle \
		(game_data->ray->angle - game_data->player->angle));
	wall_h = (TILE_SIZE / game_data->ray->distance) * ((WIN_WIDTH / 2) / \
	tan(game_data->player->fov_in_radians / 2));
	b_pix = (WIN_HEIGHT / 2) + (wall_h / 2);
	t_pix = (WIN_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > WIN_HEIGHT)
		b_pix = WIN_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	game_data->ray->index = ray;
	draw_wall(game_data, t_pix, b_pix, wall_h);
	draw_floor_ceiling(game_data, ray, t_pix, b_pix);
}
