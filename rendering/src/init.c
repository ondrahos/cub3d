/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:31:50 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/02 19:07:53 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_game game)
{
	game.player->x = game.data->px * TILE_SIZE + TILE_SIZE / 2;
	game.player->y = game.data->py * TILE_SIZE + TILE_SIZE / 2;
	game.player->fov_in_radians = (FOV * PI) / 180;
	game.player->angle = PI;
}

void	load_textures(t_game *game)
{
	game->texture->east = mlx_load_png("./textures/east.png");
	game->texture->north = mlx_load_png("./textures/north.png");
	game->texture->south = mlx_load_png("./textures/south.png");
	game->texture->west = mlx_load_png("./textures/west.png");
	game->texture->floor_color = 0xB99470FF;
	game->texture->ceiling_color = 0x89CFF3FF;
}

void	get_px_py(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->px = x;
				data->py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->map = ft_calloc(20, sizeof(char *));
	data->map[0] = strdup("111111111111111111111111111111111111");
	data->map[1] = strdup("1000000000000000000100000000000000001");
	data->map[2] = strdup("1001000000000P00000000000000000000001");
	data->map[3] = strdup("1001000000000000001000000000000000001");
	data->map[4] = strdup("1001000000000000001000000000001111111");
	data->map[5] = strdup("1001000000100000001000000000001000001");
	data->map[6] = strdup("1001000000000000001000000000001000001");
	data->map[7] = strdup("1001000000001000001000000000001000001");
	data->map[8] = strdup("1001000000000000001000000000001000001");
	data->map[9] = strdup("1001000000000000001000000000001000001");
	data->map[10] = strdup("1001000000000000001000000000001000001");
	data->map[11] = strdup("1001000000000000001000000000001000001");
	data->map[12] = strdup("1001000000000000001111111111111000001");
	data->map[13] = strdup("1001000000000000000000000000000000001");
	data->map[14] = strdup("1001000000000000000000000000000000001");
	data->map[15] = strdup("1001000000000000000000000000000000001");
	data->map[16] = strdup("1001000000000000000000000000000000001");
	data->map[17] = strdup("1001000000000000000000000000000000001");
	data->map[18] = strdup("1111111111111111111111111111111111111");
	data->map[19] = NULL;
	get_px_py(data);
	data->map_width = 38;
	data->map_height = 18;
	return (data);
}
