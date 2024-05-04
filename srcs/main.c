/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:12 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/05/04 17:12:27 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_argument(t_game *game, char **av)
{
	if (check_file(av[1], true) == FAIL)
		close_exit(game, FAIL);
	/* parse_data(av[1], game);
	if (get_file_data(data, data->mapinfo.file) == FAIL)
		return (free_data(data));
	if (check_map_validity(data, data->map) == FAIL)
		return (free_data(data));
	if (check_textures_validity(data, &data->texinfo) == FAIL)
		return (free_data(data)); */
	/* init_player_direction(data); */
	/* if (DEBUG_MSG)
		debug_display_data(data); */
	return (0);
}

int	main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
		return (print_error("Usage", "./cub3d <path/to/map.cub>", 1));
	init_data(&game);
	if (parse_argument(&game, av) != 0)
		return (1);
	init_mlx(&game);
	mlx_loop(game.mlx);
	return (0);
}
