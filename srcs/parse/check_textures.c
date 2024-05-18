/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:48:14 by daraz             #+#    #+#             */
/*   Updated: 2024/05/18 13:09:22 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (print_error_nbr(rgb[i], "Invalid RGB value. Provide value between 0 and 255", FAIL));
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

/* 
chat GPT zkratka na prevod RGB do HEX
r = 17 (0x11 in hexadecimal)
g = 38 (0x26 in hexadecimal)
b = 64 (0x40 in hexadecimal)

Binary representation:
r = 00010001
g = 00100110
b = 01000000

Now, let's apply the bitwise AND operation with 0xff (which is 11111111 in binary) to extract the least significant 8 bits:

r & 0xff = 00010001
g & 0xff = 00100110
b & 0xff = 01000000

Now, let's left-shift each component to its appropriate position in the final hexadecimal color code:

r shifted by 16 bits: 00010001 << 16 = 000100010000000000000000 (in binary)
g shifted by 8 bits: 00100110 << 8 = 000000000010011000000000 (in binary)
b: 01000000 (no shift)

Now, let's combine these values using bitwise OR:

000100010000000000000000 (r)
000000000010011000000000 (g)
000000000000000010000000 (b)
--------------------------
000100010010011010000000 (in binary)

Finally, let's convert this binary number to hexadecimal:

0001 0001 0010 0110 1000 0000 (grouped for readability)
0x112680 (in hexadecimal)

So, the resulting hexadecimal color code is 0x112680.
 */

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