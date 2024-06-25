/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:51:21 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/06 19:28:45 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_delete_textures(t_texture *texture)
{
	if (texture->north)
		mlx_delete_texture(texture->north);
	if (texture->south)
		mlx_delete_texture(texture->south);
	if (texture->west)
		mlx_delete_texture(texture->west);
	if (texture->east)
		mlx_delete_texture(texture->east);
}

void	ft_exit(t_game_data *game_data)
{
	int	i;

	i = 0;
	while (game_data->data->map[i])
		free(game_data->data->map[i++]);
	free(game_data->data->map);
	free(game_data->data);
	free(game_data->player);
	free(game_data->ray);
	ft_delete_textures(game_data->texture);
	free(game_data->texture);
	mlx_delete_image(game_data->mlx, game_data->img);
	mlx_close_window(game_data->mlx);
	mlx_terminate(game_data->mlx);
	ft_putstr_fd("Game closed\n", 1);
	exit(0);
}
