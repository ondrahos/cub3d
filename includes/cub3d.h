/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daraz <daraz@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:12:05 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/05/04 16:59:17 by daraz            ###   ########.fr       */
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

typedef struct s_game
{
    void    *mlx;
    void    *win;
    int		win_height;
	int		win_width;
}   t_game;

//parsing & init
void	init_data(t_game *game);
void	init_mlx(t_game *game);
int	    check_file(char *arg, bool is_cub);

//exit & free
void	close_exit(t_game *game, int code);
int     print_error(char *detail, char *str, int code);

#endif
