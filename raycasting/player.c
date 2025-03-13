/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:39:37 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/12 07:17:18 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_abilities(t_game *game, int i, int j)
{
	game->player.move_speed = 10;
	game->player.x = j;
	game->player.y = i;
	game->player.x_pixel = (j * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	game->player.y_pixel = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	game->player.rotaion_speed = 3 * (PI / 180);
}

int	found_player(int i, int j, t_game *game)
{
	if (game->map[i][j] == 'N')
	{
		game->player.pva = -(PI / 2);
		game->player.direction = 0;
		return (1);
	}
	else if (game->map[i][j] == 'S')
	{
		game->player.pva = (PI / 2);
		game->player.direction = 2;
		return (1);
	}
	else if (game->map[i][j] == 'E')
	{
		game->player.pva = 0;
		game->player.direction = 1;
		return (1);
	}
	else if (game->map[i][j] == 'W')
	{
		game->player.pva = PI;
		game->player.direction = 3;
		return (1);
	}
	return (0);
}

void	find_player(t_game *game)
{
	int				i;
	unsigned int	j;

	i = 0;
	while (i < game->map_len + 1)
	{
		j = 0;
		while (j < ft_strlen(game->map[i]))
		{
			if (found_player(i, j, game))
			{
				player_abilities(game, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
