/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:43:05 by daraz             #+#    #+#             */
/*   Updated: 2024/06/06 20:58:58 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static void	init_player_position(t_player_position *player)
{
	player->dir = '0';
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
	game->win_height = WIN_HEIGHT;
	game->win_width = WIN_WIDTH;
	init_texdata(&game->texdata);
	init_map(&game->map);
	init_player_position(&game->player);
	game->separate_map = NULL;
}
