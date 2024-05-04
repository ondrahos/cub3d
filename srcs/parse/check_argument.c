/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:39:10 by daraz             #+#    #+#             */
/*   Updated: 2024/05/04 16:56:40 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_dir(char *arg)
{
	int		fd;
	bool	result;

	result = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		result = true;
	}
	return (result);
}

static bool	is_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

int	check_file(char *arg, bool is_cub)
{
	int	fd;

	if (is_dir(arg))
		return (print_error(arg, "Is a directory", FAIL));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (print_error(arg, strerror(errno), FAIL));
	close(fd);
	if (is_cub && !is_cub_file(arg))
		return (print_error(arg, "The file does not end with .cub", FAIL));
	if (!is_cub && !is_xpm_file(arg))
		return (print_error(arg, "The file does not end with .xpm", FAIL));
	return (SUCC);
}