/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:02:54 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/13 09:02:56 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_filled_triangle_north(int x, int y, t_game *game, int color)
{
	int	i;
	int	j;
	int	size;

	size = 6;
	i = -size;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (j <= size - abs(i))
			{
				ft_mlx_pixel_put(game, x + i, y - j, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_filled_triangle_east(int x, int y, t_game *game, int color)
{
	int	i;
	int	j;
	int	size;

	size = 6;
	i = 0;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			if (i <= size - abs(j))
			{
				ft_mlx_pixel_put(game, x + i, y + j, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_filled_triangle_south(int x, int y, t_game *game, int color)
{
	int	i;
	int	j;
	int	size;

	size = 6;
	i = -size;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (j <= size - abs(i))
			{
				ft_mlx_pixel_put(game, x + i, y + j, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_filled_triangle_west(int x, int y, t_game *game, int color)
{
	int	i;
	int	j;
	int	size;

	size = 6;
	i = 0;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			if (i <= size - abs(j))
			{
				ft_mlx_pixel_put(game, x - i, y + j, color);
			}
			j++;
		}
		i++;
	}
}
