/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:12:05 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 20:46:50 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./MLX42/MLX42.h"
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

# define RESET	"\e[0m"
# define RED	"\e[31m"

# define WIN_WIDTH 1900
# define WIN_HEIGHT 1000
# define TILE_SIZE 30
# define ROTATION_SPEED 0.035
# define PLAYER_SPEED 2.5
# define PI 3.14159265359
# define FOV 60

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

typedef struct s_player_position
{
	char	dir;
	double	pos_x;
	double	pos_y;
}	t_player_position;

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
	int					win_height;
	int					win_width;
	t_map				map;
	t_texdata			texdata;
	char				**separate_map;
	t_player_position	player;
}	t_game;

typedef struct s_player
{
	int		x;
	int		y;
	double	angle;
	float	fov_in_radians;
	int		rotate;
	int		left_right;
	int		up_down;
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	distance;
	int		flag;
	int		index;
	double	horizontal_x;
	double	horizontal_y;
	double	vertical_x;
	double	vertical_y;
}	t_ray;

typedef struct s_data
{
	char	**map;
	int		px;
	int		py;
	int		map_width;
	int		map_height;
}	t_data;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				floor_color;
	int				ceiling_color;
}	t_texture;

typedef struct s_game_data
{
	mlx_image_t		*img;
	mlx_t			*mlx;
	t_ray			*ray;
	t_data			*data;
	t_player		*player;
	t_texture		*texture;
}	t_game_data;

//parsing & init
void			init_data(t_game *game);
void			init_texdata(t_texdata *textures);
int				check_file(char *arg, bool is_cub);
void			parse_map_file(char *path, t_game *game);
int				get_data_from_map(t_game *game, char **map);
int				get_color(t_game *game, t_texdata *textures, char *line, int j);
int				create_map(t_game *game, char **file, int i);
size_t			get_biggest_width(t_map *map, int i);
int				check_map(t_game *game, char **map_tab);
int				check_map_walls_around(t_map *map, char **map_tab);
int				is_white_space(char c);
int				check_textures(t_game *game, t_texdata *textures);

//exit & free
void			close_exit(t_game *game, int code);
int				print_error(char *detail, char *str, int code);
void			free_tab(void **tab);
int				free_game(t_game *game);
int				print_error_nbr(int detail, char *str, int code);

//game
t_data			*init_game_data(t_game game);
void			load_textures(t_game_data *game_data, t_game game);
void			init_player(t_game_data game_data);
void			cast_rays(t_game_data *game_data);
float			get_vertical_inter(t_game_data *game_data, float angle);
float			get_horizontal_inter(t_game_data *game_data, float angle);
void			render_wall(t_game_data *game_data, int ray);
float			normalize_angle(float angle);
int				wall_hit(float x, float y, t_game_data *game_data);
int				unit_circle(float angle, char c);
int				inter_check(float angle, float *inter,
					float *step, int is_horizon);
void			draw_wall(t_game_data *game_data,
					int t_pix, int b_pix, double wall_h);
double			get_x_o(mlx_texture_t *texture, t_game_data *game_data);
mlx_texture_t	*get_texture(t_game_data *game_data, int flag);
void			draw_floor_ceiling(t_game_data *game_data,
					int ray, int t_pix, int b_pix);
void			render_wall(t_game_data *game_data, int ray);
void			my_mlx_pixel_put(t_game_data *game_data,
					int x, int y, int color);
int				reverse_bytes(int c);
void			hook(t_game_data *game_data, double move_x, double move_y);
void			move_player(t_game_data *game_data,
					double move_x, double move_y);
void			rotate_player(t_game_data *game_data, int i);
void			mlx_key(mlx_key_data_t keydata, void *ptr);
void			ft_reles(mlx_key_data_t keydata, t_game_data *game_data);
void			ft_exit(t_game_data *game_data);
void			ft_delete_textures(t_texture *texture);
void			execute(t_game game);

#endif
