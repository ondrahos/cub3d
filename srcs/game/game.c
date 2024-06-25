/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:52:42 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 21:00:50 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	game_loop(void *ptr)
{
	t_game_data	*game_data;

	game_data = ptr;
	mlx_delete_image(game_data->mlx, game_data->img);
	game_data->img = mlx_new_image(game_data->mlx, WIN_WIDTH, WIN_HEIGHT);
	hook(game_data, 0, 0);
	cast_rays(game_data);
	mlx_image_to_window(game_data->mlx, game_data->img, 0, 0);
}

void	get_angle(t_game_data *game_data)
{
	char	c;

	c = game_data->data->map[game_data->data->py][game_data->data->px];
	if (c == 'N')
		game_data->player->angle = 3 * PI / 2;
	if (c == 'S')
		game_data->player->angle = PI / 2;
	if (c == 'E')
		game_data->player->angle = 0;
	if (c == 'W')
		game_data->player->angle = PI;
	game_data->player->x = (game_data->data->px * TILE_SIZE) + TILE_SIZE / 2;
	game_data->player->y = (game_data->data->py * TILE_SIZE) + TILE_SIZE / 2;
	game_data->player->fov_in_radians = (FOV * PI / 180);
}

void	start_the_game(t_data *data, t_game game)
{
	t_game_data	game_data;

	game_data.texture = ft_calloc(sizeof(t_texture), 1);
	game_data.data = data;
	game_data.player = ft_calloc(1, sizeof(t_player));
	game_data.ray = ft_calloc(1, sizeof(t_ray));
	game_data.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", 0);
	load_textures(&game_data, game);
	init_player(game_data);
	get_angle(&game_data);
	mlx_loop_hook(game_data.mlx, &game_loop, &game_data);
	mlx_key_hook(game_data.mlx, &mlx_key, &game_data);
	mlx_loop(game_data.mlx);
}

void	execute(t_game game)
{
	t_data	*data;

	data = init_game_data(game);
	start_the_game(data, game);
}
