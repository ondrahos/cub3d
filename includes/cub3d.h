/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:12:05 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/05/18 14:08:36 by daraz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

//colors

# define RESET	"\e[0m"
# define RED	"\e[31m"

/* # define WIN_WIDTH 960 */
/* # define WIN_HEIGHT 720 */
# define WIN_WIDTH 640
# define WIN_HEIGHT 480

enum e_status
{
	SUCC = 0,
	FAIL = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

typedef struct s_map
{
	char		**file;
	int			fd;
	char		*path;
	int			line_count;
	int			height;
	int			width;
	int			index_map_end;
}	t_map;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
}	t_player;

typedef struct s_texdata
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
}	t_texdata;

typedef struct s_game
{
    void    	*mlx;
    void    	*win;
    int			win_height;
	int			win_width;
	t_map		map;
	t_texdata	texdata;
	char		**separate_map;
	t_player	player;
}   t_game;

//parsing & init
void	init_data(t_game *game);
void	init_texdata(t_texdata *textures);
void	init_mlx(t_game *game);
int	    check_file(char *arg, bool is_cub);
void	parse_map_file(char *path, t_game *game);
int		get_data_from_map(t_game *game, char **map);
int		get_color(t_game *game, t_texdata *textures, char *line, int j);
int		create_map(t_game *game, char **file, int i);
size_t	get_biggest_width(t_map *map, int i);
int		check_map(t_game *game, char **map_tab);
int		check_map_walls_around(t_map *map, char **map_tab);
int		is_white_space(char c);
int		check_textures(t_game *game, t_texdata *textures);

//exit & free
void	close_exit(t_game *game, int code);
int     print_error(char *detail, char *str, int code);
void	free_tab(void **tab);
int		free_game(t_game *game);
int		print_error_nbr(int detail, char *str, int code);

#endif
