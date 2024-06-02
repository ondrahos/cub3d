/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:43:33 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/02 19:06:20 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < WIN_HEIGHT)
		my_mlx_pixel_put(game, ray, i++, game->texture->floor_color);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(game, ray, i++, game->texture->ceiling_color);
}

mlx_texture_t	*get_texture(t_game *game, int flag)
{
	game->ray->angle = normalize_angle(game->ray->angle);
	if (flag == 0)
	{
		if (game->ray->angle > PI / 2 && game->ray->angle < 3 * (PI / 2))
			return (game->texture->east);
		else
			return (game->texture->west);
	}
	else
	{
		if (game->ray->angle > 0 && game->ray->angle < PI)
			return (game->texture->south);
		else
			return (game->texture->north);
	}
}

double	get_x_o(mlx_texture_t *texture, t_game *game)
{
	double	x_o;

	if (game->ray->flag == 1)
		x_o = (int)fmodf((game->ray->horizontal_x * \
		(texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((game->ray->vertical_y * \
		(texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}

void	draw_wall(t_game *game, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(game, game->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_o = get_x_o(texture, game);
	y_o = (t_pix - (WIN_HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(game, game->ray->index, t_pix, reverse_bytes \
		(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	render_wall(t_game *game, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game->ray->distance *= cos(normalize_angle \
		(game->ray->angle - game->player->angle));
	wall_h = (TILE_SIZE / game->ray->distance) * ((WIN_WIDTH / 2) / \
	tan(game->player->fov_in_radians / 2));
	b_pix = (WIN_HEIGHT / 2) + (wall_h / 2);
	t_pix = (WIN_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > WIN_HEIGHT)
		b_pix = WIN_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	game->ray->index = ray;
	draw_wall(game, t_pix, b_pix, wall_h);
	draw_floor_ceiling(game, ray, t_pix, b_pix);
}
