/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:45:54 by daraz             #+#    #+#             */
/*   Updated: 2024/05/14 16:23:42 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_line(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error(path, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

static void	allocate_map_file(int row, int column, int i, t_game *game)
{
	char	*line;

	line = get_next_line(game->map.fd);
	while (line != NULL)
	{
		game->map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!game->map.file[row])
		{
			print_error(NULL, "Allocation failed", 0);
			return (free_tab((void **)game->map.file));
		}
		while (line[i] != '\0')
			game->map.file[row][column++] = line[i++];
		game->map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(game->map.fd);
	}
	game->map.file[row] = NULL;
}

void	parse_map_file(char *path, t_game *game)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	game->map.line_count = count_line(path);
	game->map.path = path;
	game->map.file = ft_calloc(game->map.line_count \
			+ 1, sizeof(char *));
	if (!(game->map.file))
	{
		print_error(NULL, "Allocation failed", 0);
		return ;
	}
	game->map.fd = open(path, O_RDONLY);
	if (game->map.fd < 0)
		print_error(path, strerror(errno), FAIL);
	else
	{
		allocate_map_file(row, column, i, game);
		close(game->map.fd);
	}
}
