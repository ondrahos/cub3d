/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:31:50 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 20:28:37 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

void	init_player(t_game_data game_data)
{
	game_data.player->x = game_data.data->px * TILE_SIZE + TILE_SIZE / 2;
	game_data.player->y = game_data.data->py * TILE_SIZE + TILE_SIZE / 2;
	game_data.player->fov_in_radians = (FOV * PI) / 180;
	game_data.player->angle = PI;
}

void	load_textures(t_game_data *game_data, t_game game)
{
	game_data->texture->east = mlx_load_png(game.texdata.east);
	game_data->texture->north = mlx_load_png(game.texdata.north);
	game_data->texture->south = mlx_load_png(game.texdata.south);
	game_data->texture->west = mlx_load_png(game.texdata.west);
	game_data->texture->floor_color = get_rgba(game.texdata.floor[0],
			game.texdata.floor[1], game.texdata.floor[2], 255);
	game_data->texture->ceiling_color = get_rgba(game.texdata.ceiling[0],
			game.texdata.ceiling[1], game.texdata.ceiling[2], 255);
}

t_data	*init_game_data(t_game game)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->map = game.separate_map;
	data->px = game.player.pos_x;
	data->py = game.player.pos_y;
	data->map_width = game.map.width;
	data->map_height = game.map.height;
	return (data);
}
