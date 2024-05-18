/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:43:05 by daraz             #+#    #+#             */
/*   Updated: 2024/05/18 14:08:51 by daraz            ###   ########.fr       */
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

static void	init_map(t_map *map)
{
	map->file = NULL;
	map->fd = 0;
	map->path = NULL;
	map->line_count = 0;
	map->height = 0;
	map->width = 0;
	map->index_map_end = 0;
}

static void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
}

void	init_texdata(t_texdata *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
}

void	init_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->win_height = WIN_HEIGHT;
	game->win_width = WIN_WIDTH;
	init_texdata(&game->texdata);
	init_map(&game->map);
	init_player(&game->player);
	game->separate_map = NULL;
}
