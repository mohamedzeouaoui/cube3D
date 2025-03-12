/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:17:41 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/12 07:29:52 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	found_wall(t_game *game, int x_pos, int y_pos)
{
	int	x_map;
	int	y_map;

	if (y_pos < 0 || y_pos >= (game->map_len * BLOCK_SIZE) || \
	x_pos < 0 || x_pos >= (game->map_width * BLOCK_SIZE))
		return (1);
	x_map = x_pos / BLOCK_SIZE;
	y_map = y_pos / BLOCK_SIZE;
	return (game->map[y_map][x_map] == '1');
}

double	normalize_angle(double angle)
{
	double	n_angle;

	n_angle = fmod(angle, PI * 2);
	if (n_angle < 0)
		n_angle += PI * 2;
	return (n_angle);
}

void	draw_ceiling(t_game *game, int y_start, int x_start)
{
	int	i;

	i = 0;
	while (i < y_start)
	{
		ft_mlx_pixel_put(game, x_start, i, game->c_color);
		i++;
	}
}

void	draw_floor(t_game *game, int y_start, int x_start, int wall_height)
{
	int	i;

	i = y_start + wall_height;
	while (i < HEIGHT)
	{
		ft_mlx_pixel_put(game, x_start, i, game->f_color);
		i++;
	}
}

int	found_door(t_game *game, int x_pos, int y_pos)
{
	int	x_map;
	int	y_map;

	if (x_pos < 0 || x_pos >= (game->map_width * BLOCK_SIZE) || \
	y_pos < 0 || y_pos >= (game->map_len * BLOCK_SIZE))
		return (1);
	x_map = x_pos / BLOCK_SIZE;
	y_map = y_pos / BLOCK_SIZE;
	return (game->map[y_map][x_map] == 'C');
}
