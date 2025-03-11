/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:06:33 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 20:34:11 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_wall_img2(t_game *game, double ray_angle)
{
	if (facing_west(game))
	{
		if (game->which_hit == 0)
			return (game->wall_east.tex_data);
		if (game->which_hit == 1 && ray_facing_south(ray_angle))
			return (game->wall_north.tex_data);
		if (game->which_hit == 1 && ray_facing_north(ray_angle))
			return (game->wall_south.tex_data);
	}
	else if (facing_east(game))
	{
		if (game->which_hit == 0)
			return (game->wall_west.tex_data);
		if (game->which_hit == 1 && ray_facing_west(ray_angle))
			return (game->wall_south.tex_data);
		if (game->which_hit == 1)
			return (game->wall_north.tex_data);
	}
	return (NULL);
}

char	*get_wall_img(t_game *game, double ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	if (facing_north(game))
	{
		if (game->which_hit == 1)
			return (game->wall_south.tex_data);
		if (game->which_hit == 0 && ray_facing_east(ray_angle))
			return (game->wall_west.tex_data);
		if (game->which_hit == 0 && ray_facing_west(ray_angle))
			return (game->wall_east.tex_data);
	}
	else if (facing_south(game))
	{
		if (game->which_hit == 1)
			return (game->wall_north.tex_data);
		if (game->which_hit == 0 && ray_facing_east(ray_angle))
			return (game->wall_west.tex_data);
		if (game->which_hit == 0)
			return (game->wall_east.tex_data);
	}
	return (get_wall_img2(game, ray_angle));
}

void	draw_3d(t_game *game, int x_start, int y_start
		, int wall_height)
{
	t_draw	var;

	var.tex_x = (int)(game->wall.wall_cord % BLOCK_SIZE);
	var.step = 1.0 * BLOCK_SIZE / wall_height;
	var.tex_pos = 0;
	draw_ceiling(game, y_start, x_start);
	var.y = y_start;
	while (var.y < y_start + wall_height)
	{
		var.tex_y = (int)var.tex_pos;
		var.tex_pos += var.step;
		var.pixel_index = (var.tex_y * game->wall_north.line_length) + \
		(var.tex_x * (game->wall_north.bpp / 8));
		var.color = 0;
		if (found_wall(game, game->wall_hit_x, game->wall_hit_y))
			var.color = *(int *)(get_wall_img(game, game->ray_angle) + \
			var.pixel_index);
		if (var.y >= 0 && var.y < HEIGHT)
			ft_mlx_pixel_put(game, x_start, var.y, var.color);
		var.y++;
	}
	draw_floor(game, y_start, x_start, wall_height);
}
