/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:12 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/05/18 14:10:43 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_argument(t_game *game, char **av)
{
	if (check_file(av[1], true) == FAIL)
		close_exit(game, FAIL);
	parse_map_file(av[1], game);

/* 	for (int k = 0; k < 21; k++) {
		printf("%s", game->map.file[k]);
	} */

	if (get_data_from_map(game, game->map.file) == FAIL)
		return (free_game(game));
	if (check_map(game, game->separate_map) == FAIL)
		return (free_game(game));
	if (check_textures(game, &game->texdata) == FAIL)
		return (free_game(game));

	/* printf("north = %s\nwest = %s\nceiling = %d, %d, %d\nfloor = %d, %d, %d\nhex floor = %li\nhex ceil = %li\npositin = %f/%f\n\n", 
        game->texdata.north, 
        game->texdata.west, 
        game->texdata.ceiling[0], game->texdata.ceiling[1], game->texdata.ceiling[2],
        game->texdata.floor[0], game->texdata.floor[1], game->texdata.floor[2],
		game->texdata.hex_floor,
		game->texdata.hex_ceiling,
		game->player.pos_x,
		game->player.pos_y);
		
	for (int k = 0; k < 14; k++) {
		printf("%s\n", game->separate_map[k]);
	}
	printf("\n"); */

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
