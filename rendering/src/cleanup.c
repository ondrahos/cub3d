/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohosnedl <ohosnedl@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:51:21 by ohosnedl          #+#    #+#             */
/*   Updated: 2024/06/02 18:52:14 by ohosnedl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	ft_exit(t_game *game)
{
	int	i;

	i = 0;
	while (game->data->map[i])
		free(game->data->map[i++]);
	free(game->data->map);
	free(game->data);
	free(game->player);
	free(game->ray);
	ft_delete_textures(game->texture);
	free(game->texture);
	mlx_delete_image(game->mlx, game->img);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	ft_putstr_fd("Game closed\n", 1);
	exit(0);
}
