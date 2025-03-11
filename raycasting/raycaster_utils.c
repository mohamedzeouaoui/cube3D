/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:33 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 19:56:37 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	count_distance(double x1, double x2, double y1, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	r_g_b(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
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

	i = -1;
	while (++i < y_start)
		ft_mlx_pixel_put(game, x_start, i, game->c_color);
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
