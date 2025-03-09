#include "../cub3d.h"

char *get_wall_img2(t_game *game, double ray_angle)
{
	if (facing_west(game)) //<-
	{
		if (game->which_hit == 0)//ver
			return (game->wall_east.tex_data);//gris
		if (game->which_hit == 1 && ray_facing_south(ray_angle))
			return (game->wall_north.tex_data);
		if (game->which_hit == 1 && ray_facing_north(ray_angle))
			return (game->wall_south.tex_data);
	}
	else if (facing_east(game)) // ->
	{
		if (game->which_hit == 0)//hor
			return (game->wall_west.tex_data);//gris
		if (game->which_hit == 1 && ray_facing_west(ray_angle))
			return (game->wall_south.tex_data);
		if (game->which_hit == 1)
			return (game->wall_north.tex_data);
	}
	return (NULL);
}

char *get_wall_img(t_game *game, double ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	if (facing_north(game))
	{
		if (game->which_hit == 1)//hor
			return (game->wall_south.tex_data);//yellow
		if (game->which_hit == 0 && ray_facing_east(ray_angle))
			return (game->wall_west.tex_data);
		if (game->which_hit == 0 && ray_facing_west(ray_angle))
			return (game->wall_east.tex_data);
	}
	else if (facing_south(game))
	{
		if (game->which_hit == 1)//hor
			return (game->wall_north.tex_data);//gris
		if (game->which_hit == 0 && ray_facing_east(ray_angle))
			return (game->wall_west.tex_data);
		if (game->which_hit == 0)
			return (game->wall_east.tex_data);
	}
	return (get_wall_img2(game, ray_angle));
}

void draw_3d(t_game *game, int x_start, int y_start, int wall_height, double ray_angle)
{
	int y = 0;
	int tex_x = (int)(game->wall.wall_cord % BLOCK_SIZE); // Get texture column
	double step = 1.0 * BLOCK_SIZE / wall_height;
	double tex_pos = 0;

	draw_ceiling(game, y_start, x_start);
	for (y = y_start; y < y_start + wall_height; y++)
	{
		int tex_y = (int)tex_pos; // Keep within texture bounds
		tex_pos += step;

		int pixel_index = (tex_y * game->wall_north.line_length) + (tex_x * (game->wall_north.bpp / 8));
		int color;
		if (found_wall(game, game->wall_hit_x, game->wall_hit_y))
			color = *(int *)(get_wall_img(game, ray_angle) + pixel_index);
		if (y >= 0 && y < HEIGHT)
			ft_mlx_pixel_put(game, x_start, y, color);
	}
	draw_floor(game, y_start, x_start, wall_height);
}
