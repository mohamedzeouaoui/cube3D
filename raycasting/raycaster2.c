/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:38:37 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 20:34:35 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	found_wall(t_game *game, int x_pos, int y_pos)
{
	int	x_map;
	int	y_map;

	if (x_pos < 0 || x_pos >= (game->map_width * BLOCK_SIZE) \
	|| y_pos < 0 || y_pos >= (game->map_len * BLOCK_SIZE))
		return (1);
	x_map = x_pos / BLOCK_SIZE;
	y_map = y_pos / BLOCK_SIZE;
	return (game->map[y_map][x_map] == '1');
}

void	cast_ray_init(t_game *game, t_ray *hor, t_ray *ver, double ray_angle)
{
	hor->x = 0;
	hor->y = 0;
	hor->dst = INFINITY;
	hor->ray_angle = ray_angle;
	hor->x_intercept = 0;
	hor->y_intercept = 0;
	hor->x_step = 0;
	hor->y_step = 0;
	hor->is_ray_facing_down = 0;
	hor->is_ray_facing_right = 0;
	hor->x_next_step = hor->x_intercept;
	hor->y_next_step = hor->x_intercept;
	ver->x = 0;
	ver->y = 0;
	ver->dst = INFINITY;
	ver->ray_angle = ray_angle;
	ver->x_intercept = 0;
	ver->y_intercept = 0;
	ver->x_step = 0;
	ver->y_step = 0;
	ver->is_ray_facing_down = 0;
	ver->is_ray_facing_right = 0;
	ver->x_next_step = 0;
	ver->y_next_step = 0;
	init_game(game, hor, ver);
}

void	cast_ray(t_game *game, double ray_angle, int i)
{
	t_ray	hor;
	t_ray	ver;

	cast_ray_init(game, &hor, &ver, ray_angle);
	if (hor.dst < ver.dst)
	{
		game->wall_height = (BLOCK_SIZE / (hor.dst * cos(ray_angle - \
		game->player.pva))) * ((WIDTH / 2) / tan((60 * (PI / 180)) / 2));
		game->wall.wall_cord = fmod(hor.x, BLOCK_SIZE);
		game->wall_hit_x = hor.x;
		game->wall_hit_y = hor.y;
		game->which_hit = 1;
	}
	else if (ver.dst < hor.dst)
	{
		game->wall_height = (BLOCK_SIZE / (ver.dst * cos(ray_angle - \
		game->player.pva))) * ((WIDTH / 2) / tan((60 * (PI / 180)) / 2));
		game->wall.wall_cord = fmod(ver.y, BLOCK_SIZE);
		game->wall_hit_x = ver.x;
		game->wall_hit_y = ver.y;
		game->which_hit = 0;
	}
	game->ray_angle = ray_angle;
	draw_3d(game, i, (HEIGHT / 2) - (game->wall_height / game->view_height), \
	game->wall_height);
}

void	cast_rays(t_game *game)
{
	int		i;
	double	angle_step;
	double	ray_angle;

	angle_step = (60 * (PI / 180)) / WIDTH;
	ray_angle = normalize_angle(game->player.pva - ((60 * (PI / 180)) / 2));
	i = -1;
	while (++i < WIDTH)
	{
		cast_ray(game, ray_angle, i);
		ray_angle = normalize_angle(ray_angle + angle_step);
	}
}
