/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:39:03 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/12 01:40:40 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	facing_north(t_game *game)
{
	double	angle;

	angle = fmod(game->player.pva, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle > (1.25 * PI) && angle <= (1.75 * PI));
}

int	facing_south(t_game *game)
{
	double	angle;

	angle = fmod(game->player.pva, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle > (0.25 * PI) && angle <= (0.75 * PI));
}

int	facing_west(t_game *game)
{
	double	angle;

	angle = fmod(game->player.pva, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle > (0.75 * PI) && angle < (1.25 * PI));
}

int	facing_east(t_game *game)
{
	double	angle;

	angle = fmod(game->player.pva, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle > (1.75 * PI) || angle < (0.25 * PI));
}
