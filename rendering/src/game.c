/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:52:42 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/02 19:09:14 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	game_loop(void *ptr)
{
	t_game	*game;

	game = ptr;
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	hook(game, 0, 0);
	cast_rays(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}

void	start_the_game(t_data *data)
{
	t_game	game;

	game.texture = ft_calloc(sizeof(t_texture), 1);
	game.data = data;
	game.player = ft_calloc(1, sizeof(t_player));
	game.ray = ft_calloc(1, sizeof(t_ray));
	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", 0);
	load_textures(&game);
	init_player(game);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_key_hook(game.mlx, &mlx_key, &game);
	mlx_loop(game.mlx);
}

void	execute(void)
{
	t_data	*data;

	data = init_data();
	start_the_game(data);
}

int	main(void)
{
	execute();
	return (0);
}
