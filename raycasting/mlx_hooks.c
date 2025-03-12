/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:03:29 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 20:11:06 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mv_ea_we(t_game *game)
{
	if (facing_east(game))
	{
		game->keys.left = 115;
		game->keys.right = 119;
		game->keys.forward = 97;
		game->keys.backward = 100;
		game->player.direction = 1;
	}
	else if (facing_west(game))
	{
		game->keys.left = 119;
		game->keys.right = 115;
		game->keys.forward = 100;
		game->keys.backward = 97;
		game->player.direction = 3;
	}
}

void	dynamic_control(t_game *game)
{
	if (facing_south(game))
	{
		game->keys.left = 100;
		game->keys.right = 97;
		game->keys.forward = 115;
		game->keys.backward = 119;
		game->player.direction = 2;
	}
	else if (facing_north(game))
	{
		game->keys.left = 97;
		game->keys.right = 100;
		game->keys.forward = 119;
		game->keys.backward = 115;
		game->player.direction = 0;
	}
	mv_ea_we(game);
}

void	move_player(int keycode, t_game *game, int new_pos)
{
	game->slide_amount = 0;
	if (keycode == game->keys.left)
	{
		new_pos = game->player.x_pixel - game->player.move_speed;
		if (!found_wall(game, new_pos - 5, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
	if (keycode == game->keys.right)
	{
		new_pos = game->player.x_pixel + game->player.move_speed;
		if (!found_wall(game, new_pos + 5, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
	if (keycode == game->keys.forward)
	{
		new_pos = game->player.y_pixel - game->player.move_speed;
		if (!found_wall(game, game->player.x_pixel, new_pos - 5))
			game->player.y_pixel = new_pos;
	}
	if (keycode == game->keys.backward)
	{
		new_pos = game->player.y_pixel + game->player.move_speed;
		if (!found_wall(game, game->player.x_pixel, new_pos + 5))
			game->player.y_pixel = new_pos;
	}
}

int	keys(int keycode, void *game1)
{
	t_game	*game;
	int		new_pos;

	game = game1;
	new_pos = 0;
	game->menu.entred = 0;
	if (keycode == 65362)
		game->menu.index = (game->menu.index + 1) % 2;
	else if (keycode == 65364)
		game->menu.index = (game->menu.index + 1) % 2;
	if (keycode == 65293)
		game->menu.entred = 1;
	if (keycode == 113 || 65307 == keycode)
		ft_close(game, 0);
	if (keycode == 65361)
		game->player.pva = normalize_angle(game->player.pva
				- (game->player.rotaion_speed));
	if (keycode == 65363)
		game->player.pva = normalize_angle(game->player.pva
				+ (game->player.rotaion_speed));
	dynamic_control(game);
	move_player(keycode, game, new_pos);
	return (0);
}
