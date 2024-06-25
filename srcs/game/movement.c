/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:47:30 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 20:25:28 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_reles(mlx_key_data_t keydata, t_game_data *game_data)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game_data->player->left_right = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game_data->player->left_right = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game_data->player->up_down = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		game_data->player->up_down = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game_data->player->rotate = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game_data->player->rotate = 0;
}

void	mlx_key(mlx_key_data_t keydata, void *ptr)
{
	t_game_data	*game_data;

	game_data = ptr;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS \
		|| keydata.action == MLX_REPEAT))
		ft_exit(game_data);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		game_data->player->left_right = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		game_data->player->left_right = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		game_data->player->up_down = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		game_data->player->up_down = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		game_data->player->rotate = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		game_data->player->rotate = 1;
	ft_reles(keydata, game_data);
}

void	rotate_player(t_game_data *game_data, int i)
{
	if (i == 1)
	{
		game_data->player->angle += ROTATION_SPEED;
		if (game_data->player->angle > 2 * PI)
			game_data->player->angle -= 2 * PI;
	}
	else
	{
		game_data->player->angle -= ROTATION_SPEED;
		if (game_data->player->angle < 0)
			game_data->player->angle += 2 * PI;
	}
}

void	move_player(t_game_data *game_data, double move_x, double move_y)
{
	int		map_grid_y;
	int		map_grid_x;
	int		new_x;
	int		new_y;

	new_x = roundf(game_data->player->x + move_x);
	new_y = roundf(game_data->player->y + move_y);
	map_grid_x = (new_x / TILE_SIZE);
	map_grid_y = (new_y / TILE_SIZE);
	if (game_data->data->map[map_grid_y][map_grid_x] != '1' && \
	(game_data->data->map[map_grid_y][game_data->player->x
		/ TILE_SIZE] != '1' && \
	game_data->data->map[game_data->player->y / TILE_SIZE][map_grid_x] != '1'))
	{
		game_data->player->x = new_x;
		game_data->player->y = new_y;
	}
}

void	hook(t_game_data *game_data, double move_x, double move_y)
{
	if (game_data->player->rotate == 1)
		rotate_player(game_data, 1);
	if (game_data->player->rotate == -1)
		rotate_player(game_data, 0);
	if (game_data->player->left_right == 1)
	{
		move_x = -sin(game_data->player->angle) * PLAYER_SPEED;
		move_y = cos(game_data->player->angle) * PLAYER_SPEED;
	}
	if (game_data->player->left_right == -1)
	{
		move_x = sin(game_data->player->angle) * PLAYER_SPEED;
		move_y = -cos(game_data->player->angle) * PLAYER_SPEED;
	}
	if (game_data->player->up_down == 1)
	{
		move_x = cos(game_data->player->angle) * PLAYER_SPEED;
		move_y = sin(game_data->player->angle) * PLAYER_SPEED;
	}
	if (game_data->player->up_down == -1)
	{
		move_x = -cos(game_data->player->angle) * PLAYER_SPEED;
		move_y = -sin(game_data->player->angle) * PLAYER_SPEED;
	}
	move_player(game_data, move_x, move_y);
}
