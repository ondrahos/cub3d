/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:59:15 by daraz             #+#    #+#             */
/*   Updated: 2024/05/18 12:43:26 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_elements(t_game *game, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	game->player.dir = '0';
	while (map_tab[i] != NULL)
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (game->separate_map[i][j] == ' ' || game->separate_map[i][j] == '\t'
			|| game->separate_map[i][j] == '\r'
			|| game->separate_map[i][j] == '\v' || game->separate_map[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_tab[i][j])))
				return (print_error(game->map.path, "Invalid character in map", FAIL));
			if (ft_strchr("NSEW", map_tab[i][j]) && game->player.dir != '0')
				return (print_error(game->map.path, "More than one player in map", FAIL));
			if (ft_strchr("NSEW", map_tab[i][j]) && game->player.dir == '0')
				game->player.dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (SUCC);
}

static int	check_valid_position(t_game *game, char **map_tab)
{
	int	i;
	int	j;

	i = (int)game->player.pos_y;
	j = (int)game->player.pos_x;
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| is_white_space(map_tab[i][j - 1]) == SUCC
		|| is_white_space(map_tab[i][j + 1]) == SUCC
		|| is_white_space(map_tab[i - 1][j]) == SUCC
		|| is_white_space(map_tab[i + 1][j]) == SUCC)
		return (FAIL);
	return (SUCC);
}

static int	check_player_position(t_game *game, char **map_tab)
{
	int	i;
	int	j;

	if (game->player.dir == '0')
		return (print_error(game->map.path, "Map has no player spawning position", FAIL));
	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("NSEW", map_tab[i][j]))
			{
				game->player.pos_x = (double)j + 0.5;
				game->player.pos_y = (double)i + 0.5;
				map_tab[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_valid_position(game, map_tab) == FAIL)
		return (print_error(game->map.path, "Invalid player position", FAIL));
	return (SUCC);
}

static int	check_map_is_last_element(t_map *map)
{
	int	i;
	int	j;

	i = map->index_map_end;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (FAIL);
			j++;
		}
		i++;
	}
	return (SUCC);
}

int	check_map(t_game *game, char **map_tab)
{
	if (!game->separate_map)
		return (print_error(game->map.path, "No map provided", FAIL));
	if (check_map_walls_around(&game->map, map_tab) == FAIL)
		return (print_error(game->map.path, "Map is not surrounded by walls", FAIL));
	if (game->map.height < 3)
		return (print_error(game->map.path, "Map is too small, should be at least 3 lines high", FAIL));
	if (check_elements(game, map_tab) == FAIL)
		return (FAIL);
	if (check_player_position(game, map_tab) == FAIL)
		return (FAIL);
	if (check_map_is_last_element(&game->map) == FAIL)
		return (print_error(game->map.path, "Map is not the last element in file", FAIL));
	return (SUCC);
}