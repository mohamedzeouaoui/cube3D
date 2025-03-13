/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:46:46 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/12 21:24:06 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_right(t_game *game, int new_pos)
{
	float	s_a;

	s_a = 0;
	new_pos = game->player.x_pixel + game->player.move_speed;
	if (!found_wall(game, new_pos + 5, game->player.y_pixel) && \
		!found_door(game, new_pos + 5, game->player.y_pixel))
		game->player.x_pixel = new_pos;
	else if (facing_east(game))
	{
		s_a = game->player.move_speed * sinf(game->player.pva);
		new_pos = game->player.y_pixel + s_a;
		if (!found_wall(game, game->player.x_pixel, new_pos + s_a) && \
			!found_door(game, game->player.x_pixel, new_pos + s_a))
			game->player.y_pixel = new_pos;
	}
	else if (facing_west(game))
	{
		s_a = game->player.move_speed * sinf(game->player.pva);
		new_pos = game->player.y_pixel - s_a;
		if (!found_wall(game, game->player.x_pixel, new_pos - s_a) && \
			!found_door(game, game->player.x_pixel, new_pos - s_a))
			game->player.y_pixel = new_pos;
	}
}

void	move_forward(t_game *game, int new_pos)
{
	float	s_a;

	s_a = 0;
	new_pos = game->player.y_pixel - game->player.move_speed;
	if (!found_wall(game, game->player.x_pixel, new_pos - 5) && \
		!found_door(game, game->player.x_pixel, new_pos - 5))
		game->player.y_pixel = new_pos;
	else if (facing_north(game))
	{
		s_a = game->player.move_speed * cosf(game->player.pva);
		new_pos = game->player.x_pixel + s_a;
		if (!found_wall(game, new_pos + s_a, game->player.y_pixel) && \
			!found_door(game, new_pos + s_a, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
	else if (facing_south(game))
	{
		s_a = game->player.move_speed * cosf(game->player.pva);
		new_pos = game->player.x_pixel - s_a;
		if (!found_wall(game, new_pos - s_a, game->player.y_pixel) && \
			!found_door(game, new_pos - s_a, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
}

void	move_backward(t_game *game, int new_pos)
{
	float	s_a;

	s_a = 0;
	new_pos = game->player.y_pixel + game->player.move_speed;
	if (!found_wall(game, game->player.x_pixel, new_pos + s_a) && \
		!found_door(game, game->player.x_pixel, new_pos + s_a))
		game->player.y_pixel = new_pos;
	else if (facing_south(game))
	{
		s_a = game->player.move_speed * cosf(game->player.pva);
		new_pos = game->player.x_pixel + s_a;
		if (!found_wall(game, new_pos + s_a, game->player.y_pixel) && \
			!found_door(game, new_pos + s_a, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
	else if (facing_north(game))
	{
		s_a = game->player.move_speed * cosf(game->player.pva);
		new_pos = game->player.x_pixel - s_a;
		if (!found_wall(game, new_pos - s_a, game->player.y_pixel) && \
			!found_door(game, new_pos - s_a, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
}

void	move_left(t_game *game, int new_pos)
{
	float	s_a;

	s_a = 0;
	new_pos = game->player.x_pixel - game->player.move_speed;
	if (!found_wall(game, new_pos - 5, game->player.y_pixel) && \
		!found_door(game, new_pos - 5, game->player.y_pixel))
		game->player.x_pixel = new_pos;
	else if (facing_west(game))
	{
		s_a = game->player.move_speed * sinf(game->player.pva);
		new_pos = game->player.y_pixel + s_a;
		if (!found_wall(game, game->player.x_pixel, new_pos + s_a) && \
			!found_door(game, game->player.x_pixel, new_pos + s_a))
			game->player.y_pixel = new_pos;
	}
	else if (facing_east(game))
	{
		s_a = game->player.move_speed * sinf(game->player.pva);
		new_pos = game->player.y_pixel - s_a;
		if (!found_wall(game, game->player.x_pixel, new_pos - s_a) && \
			!found_door(game, game->player.x_pixel, new_pos - s_a))
			game->player.y_pixel = new_pos;
	}
}

int	keys(int keycode, void *game1)
{
	t_game	*game;
	int		new_pos;

	game = game1;
	new_pos = 0;
	if (keycode == 113 || 65307 == keycode)
		ft_close(game, 0);
	if (keycode == 65361)
		game->player.pva = normalize_angle(game->player.pva
				- (game->player.rotaion_speed));
	if (keycode == 65363)
		game->player.pva = normalize_angle(game->player.pva
				+ (game->player.rotaion_speed));
	dynamic_control(game);
	if (keycode == game->keys.left)
		move_left(game, new_pos);
	else if (keycode == game->keys.right)
		move_right(game, new_pos);
	else if (keycode == game->keys.forward)
		move_forward(game, new_pos);
	else if (keycode == game->keys.backward)
		move_backward(game, new_pos);
	return (0);
}
