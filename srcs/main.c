/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:53:12 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/05/04 13:42:51 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	(void)av;
	t_game game;

	if (ac != 2)
		return (print_error("Usage", "./cub3d <path/to/map.cub>", 1));
	init_data(&game);
	//parse args
	init_mlx(&game);
	mlx_loop(game.mlx);
	return (0);
}
