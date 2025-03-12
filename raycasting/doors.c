/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:05:36 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/12 21:10:47 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_animation(t_game *game, t_tex *image)
{
	int	color;
	int	y_start;
	int	x_start;

	y_start = HEIGHT - image->height;
	while (y_start < HEIGHT)
	{
		x_start = WIDTH / 2 - image->width / 2;
		while (x_start < WIDTH / 2 + image->width / 2)
		{
			color = *(unsigned int *)(image->tex_data + (4 * image->width * \
			(y_start - (HEIGHT - image->height)) + 4 * (x_start - \
			(WIDTH / 2 - image->width / 2))));
			if (color != 0xff000000)
				ft_mlx_pixel_put(game, x_start, y_start, color);
			x_start++;
		}
		y_start++;
	}
}

void	mv_ea_we(t_game *game)
{
	if (facing_east(game))
	{
		game->keys.left = (int) 's';
		game->keys.right = (int) 'w';
		game->keys.forward = (int) 'a';
		game->keys.backward = (int) 'd';
		game->player.direction = 1;
	}
	else if (facing_west(game))
	{
		game->keys.left = (int) 'w';
		game->keys.right = (int) 's';
		game->keys.forward = (int) 'd';
		game->keys.backward = (int) 'a';
		game->player.direction = 3;
	}
}

void	dynamic_control(t_game *game)
{
	if (facing_south(game))
	{
		game->keys.left = (int) 'd';
		game->keys.right = (int) 'a';
		game->keys.forward = (int) 's';
		game->keys.backward = (int) 'w';
		game->player.direction = 2;
	}
	else if (facing_north(game))
	{
		game->keys.left = (int) 'a';
		game->keys.right = (int) 'd';
		game->keys.forward = (int) 'w';
		game->keys.backward = (int) 's';
		game->player.direction = 0;
	}
	else
		mv_ea_we(game);
}

int	doors(int keycode, t_game *game)
{
	int	x;
	int	y;

	if (keycode == (int) 'e')
	{
		y = game->player.y_pixel / BLOCK_SIZE;
		x = game->player.x_pixel / BLOCK_SIZE;
		if (facing_south(game) && game->map[y + 1][x] == 'C')
			game->map[y + 1][x] = 'O';
		else if (facing_north(game) && game->map[y - 1][x] == 'C')
			game->map[y - 1][x] = 'O';
		else if (facing_east(game) && game->map[y][x + 1] == 'C')
			game->map[y][x + 1] = 'O';
		else if (facing_west(game) && game->map[y][x - 1] == 'C')
			game->map[y][x - 1] = 'O';
		else if (facing_south(game) && game->map[y + 1][x] == 'O')
			game->map[y + 1][x] = 'C';
		else if (facing_north(game) && game->map[y - 1][x] == 'O')
			game->map[y - 1][x] = 'C';
		else if (facing_east(game) && game->map[y][x + 1] == 'O')
			game->map[y][x + 1] = 'C';
		else if (facing_west(game) && game->map[y][x - 1] == 'O')
			game->map[y][x - 1] = 'C';
	}
	return (0);
}

int	animation(int keycode, int x, int y, t_game *game)
{
	if (keycode == 1)
		game->animation = 1;
	return (0);
}
