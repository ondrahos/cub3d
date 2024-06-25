/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:48:14 by daraz             #+#    #+#             */
/*   Updated: 2024/06/06 20:31:22 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (print_error_nbr(rgb[i],
					"Invalid RGB value. Provide value between 0 and 255",
					FAIL));
		i++;
	}
	return (SUCC);
}

static unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	check_textures(t_game *game, t_texdata *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (print_error(game->map.path, "Missing textures", FAIL));
	if (!textures->floor || !textures->ceiling)
		return (print_error(game->map.path, "Missing colors", FAIL));
	if (check_file(textures->north, false) == FAIL
		|| check_file(textures->south, false) == FAIL
		|| check_file(textures->west, false) == FAIL
		|| check_file(textures->east, false) == FAIL
		|| check_valid_rgb(textures->floor) == FAIL
		|| check_valid_rgb(textures->ceiling) == FAIL)
		return (FAIL);
	textures->hex_floor = convert_rgb_to_hex(textures->floor);
	textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	return (SUCC);
}
