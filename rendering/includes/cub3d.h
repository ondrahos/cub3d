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

# include "./MLX42/MLX42.h"
# include "./libft/libft.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define WIN_WIDTH 1900
# define WIN_HEIGHT 1000
# define TILE_SIZE 30
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define PI 3.14159265359
# define FOV 60

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

typedef struct s_game
{
	mlx_image_t		*img;
	mlx_t			*mlx;
	t_ray			*ray;
	t_data			*data;
	t_player		*player;
	t_texture		*texture;
}	t_game;


t_data			*init_data(void);
void			load_textures(t_game *game);
void 			init_player(t_game game);
void			cast_rays(t_game *game);
float			get_vertical_inter(t_game *game, float angle);
float			get_horizontal_inter(t_game *game, float angle);
void			render_wall(t_game *game, int ray);
float			normalize_angle(float angle);
int				wall_hit(float x, float y, t_game *game);
int				unit_circle(float angle, char c);
int				inter_check(float angle, float *inter, float *step, int is_horizon);
void			draw_wall(t_game *game, int t_pix, int b_pix, double wall_h);
double			get_x_o(mlx_texture_t *texture, t_game *game);
mlx_texture_t	*get_texture(t_game *game, int flag);
void			draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix);
void			render_wall(t_game *game, int ray);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
int				reverse_bytes(int c);
void			hook(t_game *game, double move_x, double move_y);
void			move_player(t_game *game, double move_x, double move_y);
void			rotate_player(t_game *game, int i)	;
void 			mlx_key(mlx_key_data_t keydata, void *ptr);
void			ft_reles(mlx_key_data_t keydata, t_game *game);
void			ft_exit(t_game *game);
void			ft_delete_textures(t_texture *texture);

#endif
