/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:37:05 by daraz             #+#    #+#             */
/*   Updated: 2024/06/19 19:22:44 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	count_map_lines(t_game *game, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	game->map.index_map_end = i;
	return (i - index_value);
}

static int	fill_map(t_map *map, char **map_tab, int index)
{
	int		i;
	int		j;

	map->width = get_biggest_width(map, index);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map_tab[i])
			return (print_error(NULL, "Allocation failed", FAIL));
		while (map->file[index][j] && map->file[index][j] != '\n')
		{
			map_tab[i][j] = map->file[index][j];
			j++;
		}
		while (j < map->width)
			map_tab[i][j++] = '\0';
		i++;
		index++;
	}
	map_tab[i] = NULL;
	return (SUCC);
}

static int	allocate_and_fill_map(t_game *game, char **file, int i)
{
	game->map.height = count_map_lines(game, file, i);
	game->separate_map = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->separate_map)
		return (print_error(NULL, "Allocation failed", FAIL));
	if (fill_map(&game->map, game->separate_map, i) == FAIL)
		return (FAIL);
	return (SUCC);
}

static void	convert_walls(t_game *game)
{
	int	i;
	int	j;
	int	max_width;

	i = 0;
	max_width = game->map.width;
	while (game->separate_map[i])
	{
		j = 0;
		while (j < max_width)
		{
			if (game->separate_map[i][j] == ' '
			|| game->separate_map[i][j] == '\t'
			|| game->separate_map[i][j] == '\v'
			|| game->separate_map[i][j] == '\f')
				game->separate_map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	create_map(t_game *game, char **file, int i)
{
	if (allocate_and_fill_map(game, file, i) == FAIL)
		return (FAIL);
	convert_walls(game);
	return (SUCC);
}
