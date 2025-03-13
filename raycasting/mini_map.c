/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:02:46 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/13 10:04:11 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square2(t_game *game, int x_start, int y_start, int color)
{
	int	y;
	int	x;

	y = y_start;
	while (y < y_start + 15)
	{
		x = x_start;
		while (x < x_start + 15)
		{
			ft_mlx_pixel_put(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_arrow(t_game *game, int x, int y, int color)
{
	x += 6;
	y += 6;
	if (game->player.direction == 0)
		draw_filled_triangle_north(x, y, game, color);
	else if (game->player.direction == 1)
		draw_filled_triangle_east(x, y, game, color);
	else if (game->player.direction == 2)
		draw_filled_triangle_south(x, y, game, color);
	else if (game->player.direction == 3)
		draw_filled_triangle_west(x, y, game, color);
}

void	map_boundries(t_game *game, t_map *var)
{
	while (var->k < var->mini_map_height)
	{
		var->l = 0;
		while (var->l < var->mini_map_width)
		{
			draw_square2(game, var->l * 15, var->k * 15, 0x000000);
			var->l++;
		}
		var->k++;
	}
}

void	draw_map_content(t_game *game, t_map *var)
{
	while (var->y < var->player_y + var->mini_map_height / 2)
	{
		var->x_off = 0;
		var->x = var->player_x - var->mini_map_width / 2;
		while (var->x < var->player_x + var->mini_map_width / 2)
		{
			if (var->y >= 0 && var->y < game->map_len && var->x >= 0 && \
			var->x < game->map_width)
			{
				if (game->map[var->y][var->x] == '1')
					draw_square2(game, var->x_off, var->y_off, 0x1c2367);
				else if (game->map[var->y][var->x] == 'C')
					draw_square2(game, var->x_off, var->y_off, 0xce0000);
				else if (game->map[var->y][var->x] == 'O')
					draw_square2(game, var->x_off, var->y_off, 0x19e62c);
				else if (game->map[var->y][var->x] == '0' || \
				ft_strchr("NSWE", game->map[var->y][var->x]))
					draw_square2(game, var->x_off, var->y_off, game->f_color);
			}
			var->x_off += 15;
			var->x++;
		}
		var->y_off += 15;
		var->y++;
	}
}

void	draw_mini_map(t_game *game)
{
	t_map	var;

	var.mini_map_width = 10;
	var.mini_map_height = 8;
	var.player_x = game->player.x_pixel / BLOCK_SIZE;
	var.player_y = game->player.y_pixel / BLOCK_SIZE;
	var.y_off = 0;
	var.k = 0;
	map_boundries(game, &var);
	var.y = var.player_y - var.mini_map_height / 2;
	draw_map_content(game, &var);
	draw_arrow(game, (var.mini_map_width / 2) * 15, (var.mini_map_height / 2) \
	* 15, 0x236413);
}
