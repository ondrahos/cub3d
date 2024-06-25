/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:12 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 20:21:31 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_argument(t_game *game, char **av)
{
	if (check_file(av[1], true) == FAIL)
		close_exit(game, FAIL);
	parse_map_file(av[1], game);
	if (get_data_from_map(game, game->map.file) == FAIL)
		return (free_game(game));
	if (check_map(game, game->separate_map) == FAIL)
		return (free_game(game));
	if (check_textures(game, &game->texdata) == FAIL)
		return (free_game(game));
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (print_error("Usage", "./cub3d <path/to/map.cub>", 1));
	init_data(&game);
	if (parse_argument(&game, av) != 0)
		return (1);
	execute(game);
	return (0);
}
