/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:26:04 by daraz             #+#    #+#             */
/*   Updated: 2024/05/16 15:15:58 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	not_digit(char *str)
{
	int		i;
	bool	not_digit;

	i = 0;
	not_digit = true;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			not_digit = false;
		i++;
	}
	return (not_digit);
}

static int	*rgb_to_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || not_digit(rgb_to_convert[i]) == true)
		{
			free_tab((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	free_tab((void **)rgb_to_convert);
	return (rgb);
}

static int	*set_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		print_error(NULL, "Allocation failed", 0);
		return (0);
	}
	return (rgb_to_array(rgb_to_convert, rgb));
}

int	get_color(t_game *game, t_texdata *textures, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (print_error(game->map.path, "Invalid floor/ceiling RGB colors", ERR));
	if (!textures->ceiling && line[j] == 'C')
	{
		textures->ceiling = set_rgb_colors(line + j + 1);
		if (textures->ceiling == 0)
			return (print_error(game->map.path, "Invalid ceiling RGB color", ERR));
	}
	else if (!textures->floor && line[j] == 'F')
	{
		textures->floor = set_rgb_colors(line + j + 1);
		if (textures->floor == 0)
			return (print_error(game->map.path, "Invalid floor RGB color", ERR));
	}
	else
		return (print_error(game->map.path, "Invalid floor/ceiling RGB colors", ERR));
	return (SUCC);
}