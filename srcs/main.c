/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:12 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/05/04 17:09:41 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_argument(t_game *game, char **av)
{
	if (check_file(av[1], true) == FAIL)
		close_exit(game, FAIL);
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
