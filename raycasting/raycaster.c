/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:47 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 19:38:29 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	hor_rays2(t_game *game, t_ray *hor)
{
	hor->x_next_step = hor->x_intercept;
	hor->y_next_step = hor->y_intercept;
	if (!hor->is_ray_facing_down)
		hor->y_next_step -= 0.001;
	while (1)
	{
		if (found_wall(game, hor->x_next_step, hor->y_next_step))
		{
			hor->dst = count_distance(game->player.x_pixel, hor->x_next_step,
					game->player.y_pixel, hor->y_next_step);
			hor->x = hor->x_next_step;
			hor->y = hor->y_next_step;
			return ;
		}
		hor->x_next_step += hor->x_step;
		hor->y_next_step += hor->y_step;
	}
}

void	hor_rays(t_game *game, t_ray *hor)
{
	hor->is_ray_facing_down = (hor->ray_angle > 0 && hor->ray_angle < PI);
	hor->is_ray_facing_right = (hor->ray_angle < (0.5 * PI)
			|| hor->ray_angle > (PI * 1.5));
	hor->y_intercept = floor(game->player.y_pixel / BLOCK_SIZE) * BLOCK_SIZE;
	if (hor->is_ray_facing_down)
		hor->y_intercept += BLOCK_SIZE;
	hor->x_intercept = game->player.x_pixel + \
			((hor->y_intercept - game->player.y_pixel) / tan(hor->ray_angle));
	hor->y_step = BLOCK_SIZE;
	if (!hor->is_ray_facing_down)
		hor->y_step *= -1;
	hor->x_step = (BLOCK_SIZE / tan(hor->ray_angle));
	if (!hor->is_ray_facing_right && hor->x_step > 0)
		hor->x_step *= -1;
	if (hor->is_ray_facing_right && hor->x_step < 0)
		hor->x_step *= -1;
	hor_rays2(game, hor);
}

void	vert_rays2(t_game *game, t_ray *ver)
{
	ver->x_next_step = ver->x_intercept;
	ver->y_next_step = ver->y_intercept;
	if (!ver->is_ray_facing_right)
		ver->x_next_step -= 0.001;
	while (ver->y_next_step > 0 && ver->x_next_step > 0)
	{
		if (found_wall(game, ver->x_next_step, ver->y_next_step))
		{
			ver->dst = count_distance(game->player.x_pixel,
					ver->x_next_step, game->player.y_pixel, ver->y_next_step);
			ver->x = ver->x_next_step;
			ver->y = ver->y_next_step;
			return ;
		}
		ver->x_next_step += ver->x_step;
		ver->y_next_step += ver->y_step;
	}
}

void	vert_rays(t_game *game, t_ray *ver)
{
	ver->x_intercept = 0;
	ver->y_intercept = 0;
	ver->x_step = 0;
	ver->y_step = 0;
	ver->is_ray_facing_down = (ver->ray_angle > 0 && ver->ray_angle < PI);
	ver->is_ray_facing_right = (ver->ray_angle < (0.5 * PI)
			|| ver->ray_angle > (PI * 1.5));
	ver->x_intercept = floor(game->player.x_pixel / BLOCK_SIZE) * BLOCK_SIZE;
	if (ver->is_ray_facing_right)
		ver->x_intercept += BLOCK_SIZE;
	ver->y_intercept = game->player.y_pixel + \
			((ver->x_intercept - game->player.x_pixel) * tan(ver->ray_angle));
	ver->x_step = BLOCK_SIZE;
	if (!ver->is_ray_facing_right)
		ver->x_step *= -1;
	ver->y_step = (BLOCK_SIZE * tan(ver->ray_angle));
	if (!ver->is_ray_facing_down && ver->y_step > 0)
		ver->y_step *= -1;
	if (ver->is_ray_facing_down && ver->y_step < 0)
		ver->y_step *= -1;
	vert_rays2(game, ver);
}

void	init_game(t_game *game, t_ray *hor, t_ray *ver)
{
	game->which_hit = -1;
	game->wall.wall_cord = 0;
	game->wall.vert = 0;
	game->wall.hor = 0;
	game->wall_height = 0;
	hor_rays(game, hor);
	vert_rays(game, ver);
}
