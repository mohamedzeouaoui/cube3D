/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:04:47 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 10:05:35 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	facing_north(t_game *game)
{
	return ((game->player.pva > (225 * (PI / 180))
		&& game->player.pva < (315 * (PI / 180)))
		|| game->player.pva == -(PI / 2));
}

int	facing_south(t_game *game)
{
	return (game->player.pva > (45 * (PI / 180))
		&& game->player.pva < (135 * (PI / 180)));
}

int	facing_west(t_game *game)
{
	return (game->player.pva > (135 * (PI / 180))
		&& game->player.pva < (225 * (PI / 180)));
}

int	facing_east(t_game *game)
{
	return (game->player.pva > (315 * (PI / 180))
		|| game->player.pva < (45 * (PI / 180)));
}
