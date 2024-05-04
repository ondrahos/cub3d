/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:43:05 by daraz             #+#    #+#             */
/*   Updated: 2024/05/04 11:35:40 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		close_exit(game, print_error("mlx", "Fail to start mlx", 1));
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
		close_exit(game, print_error("mlx", "Fail to create mlx window", 1));
	return ;
}

void	init_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->win_height = WIN_HEIGHT;
	game->win_width = WIN_WIDTH;
}