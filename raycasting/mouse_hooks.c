/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:37:04 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/12 07:36:58 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_config1(t_game *game)
{
	game->keys.left = 100;
	game->keys.right = 97;
	game->keys.forward = 115;
	game->keys.backward = 119;
	game->player.direction = 1;
}

void	mouse_config2(t_game *game)
{
	game->keys.left = 97;
	game->keys.right = 100;
	game->keys.forward = 119;
	game->keys.backward = 115;
	game->player.direction = 0;
}

void	mouse_config3(t_game *game)
{
	game->keys.left = 115;
	game->keys.right = 119;
	game->keys.forward = 97;
	game->keys.backward = 100;
	game->player.direction = 2;
}

void	mouse_config4(t_game *game)
{
	game->keys.left = 119;
	game->keys.right = 115;
	game->keys.forward = 100;
	game->keys.backward = 97;
	game->player.direction = 3;
}

int	mouse_move_hook(int x, int y, void *game1)
{
	static int	last_x = -1;
	t_game		*game;

	game = (t_game *)game1;
	if (last_x == -1)
		last_x = x;
	if (x > last_x)
		game->player.pva = normalize_angle(game->player.pva + \
		(game->player.rotaion_speed));
	else if (x < last_x)
		game->player.pva = normalize_angle(game->player.pva - \
		(game->player.rotaion_speed));
	last_x = x;
	if (facing_east(game))
		mouse_config1(game);
	else if (facing_north(game))
		mouse_config2(game);
	else if (facing_south(game))
		mouse_config3(game);
	else if (facing_west(game))
		mouse_config4(game);
	return (0);
}
