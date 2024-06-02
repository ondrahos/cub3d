/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:47:30 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/02 19:09:47 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_reles(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game->player->left_right = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game->player->left_right = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game->player->up_down = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		game->player->up_down = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->player->rotate = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->player->rotate = 0;
}

void	mlx_key(mlx_key_data_t keydata, void *ptr)
{
	t_game	*game;

	game = ptr;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS \
		|| keydata.action == MLX_REPEAT))
		ft_exit(game);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game->player->left_right = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game->player->left_right = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		game->player->up_down = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game->player->up_down = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game->player->rotate = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game->player->rotate = 1;
	ft_reles(keydata, game);
}

void	rotate_player(t_game *game, int i)
{
	if (i == 1)
	{
		game->player->angle += ROTATION_SPEED;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI;
	}
	else
	{
		game->player->angle -= ROTATION_SPEED;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
	}
}

void	move_player(t_game *game, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(game->player->x + move_x);
	new_y = roundf(game->player->y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (game->data->map[map_grid_y][map_grid_x] != '1' && \
	(game->data->map[map_grid_y][game->player->x / TILE_SIZE] != '1' && \
	game->data->map[game->player->y / TILE_SIZE][map_grid_x] != '1'))
	{
		game->player->x = new_x;
		game->player->y = new_y;
	}
}

void	hook(t_game *game, double move_x, double move_y)
{
	if (game->player->rotate == 1)
		rotate_player(game, 1);
	if (game->player->rotate == -1)
		rotate_player(game, 0);
	if (game->player->left_right == 1)
	{
		move_x = -sin(game->player->angle) * PLAYER_SPEED;
		move_y = cos(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->left_right == -1)
	{
		move_x = sin(game->player->angle) * PLAYER_SPEED;
		move_y = -cos(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->up_down == 1)
	{
		move_x = cos(game->player->angle) * PLAYER_SPEED;
		move_y = sin(game->player->angle) * PLAYER_SPEED;
	}
	if (game->player->up_down == -1)
	{
		move_x = -cos(game->player->angle) * PLAYER_SPEED;
		move_y = -sin(game->player->angle) * PLAYER_SPEED;
	}
	move_player(game, move_x, move_y);
}
