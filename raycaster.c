#include "cub3d.h"

void hor_rays(t_game *game, t_ray *hor)
{
	double x_intercept = 0, y_intercept = 0;
	double x_step = 0, y_step = 0;
	int is_ray_facing_down = (hor->ray_angle > 0 && hor->ray_angle < PI);
	int is_ray_facing_right = (hor->ray_angle < (0.5 * PI) || hor->ray_angle > (PI * 1.5));

	y_intercept = floor(game->player.y_pixel / BLOCK_SIZE) * BLOCK_SIZE;
	if (is_ray_facing_down)
		y_intercept += BLOCK_SIZE;
	x_intercept = game->player.x_pixel + ((y_intercept - game->player.y_pixel) / tan(hor->ray_angle));

	y_step = BLOCK_SIZE;
	if (!is_ray_facing_down)
		y_step *= -1;

	x_step = (BLOCK_SIZE / tan(hor->ray_angle));
	if (!is_ray_facing_right && x_step > 0)
		x_step *= -1;
	if (is_ray_facing_right && x_step < 0)
		x_step *= -1;

	double x_next_step = x_intercept;
	double y_next_step = y_intercept;
	if (!is_ray_facing_down)
		y_next_step--;
	while(1)
	{
		if (found_wall(game, x_next_step, y_next_step) || found_door(game, x_next_step, y_next_step))
		{
			hor->dst = count_distance(game->player.x_pixel, x_next_step, game->player.y_pixel, y_next_step);
			hor->x = x_next_step;
			hor->y = y_next_step;
			return ;
		}
		else
		{
			x_next_step += x_step;
			y_next_step += y_step;
		}
	}
}

void vert_rays(t_game *game, t_ray *ver)
{
	double x_intercept = 0, y_intercept = 0;
	double x_step = 0, y_step = 0;
	int is_ray_facing_down = (ver->ray_angle > 0 && ver->ray_angle < PI);
	int is_ray_facing_right = (ver->ray_angle < (0.5 * PI) || ver->ray_angle > (PI * 1.5));

	x_intercept = floor(game->player.x_pixel / BLOCK_SIZE) * BLOCK_SIZE;
	if (is_ray_facing_right)
		x_intercept += BLOCK_SIZE;
	y_intercept = game->player.y_pixel + ((x_intercept - game->player.x_pixel) * tan(ver->ray_angle));

	x_step = BLOCK_SIZE;
	if (!is_ray_facing_right)
		x_step *= -1;

	y_step = (BLOCK_SIZE * tan(ver->ray_angle));
	if (!is_ray_facing_down && y_step > 0)
		y_step *= -1;
	if (is_ray_facing_down && y_step < 0)
		y_step *= -1;

	double x_next_step = x_intercept;
	double y_next_step = y_intercept;
	if (!is_ray_facing_right)
		x_next_step--;
	while(y_next_step > 0 && x_next_step > 0)
	{
		if (found_wall(game, x_next_step, y_next_step) || found_door(game, x_next_step, y_next_step))
		{
			ver->dst = count_distance(game->player.x_pixel, x_next_step, game->player.y_pixel, y_next_step);
			ver->x = x_next_step;
			ver->y = y_next_step;
			return ;
		}
		else
		{
			x_next_step += x_step;
			y_next_step += y_step;
		}
	}
}

void draw_3d(t_game *game, int x_start, int y_start, int wall_height)
{
	int y = 0;
	int tex_x = (int)(game->wall.wall_cord % BLOCK_SIZE); // Get texture column
	double step = 1.0 * BLOCK_SIZE / wall_height;
	double tex_pos = 0;

	// Draw ceiling
	for (int i = 0; i < y_start; i++)
		ft_mlx_pixel_put(game, x_start, i, 0x025B8E);
	for (y = y_start; y < y_start + wall_height; y++)
	{
		int tex_y = (int)tex_pos; // Keep within texture bounds
		tex_pos += step;

		int pixel_index = (tex_y * game->wall.line_length) + (tex_x * (game->wall.bpp / 8));
		int color;
		if (found_door(game, game->wall_hit_x, game->wall_hit_y))
			color = *(int *)(game->door.tex_data + pixel_index);
		else if (found_wall(game, game->wall_hit_x, game->wall_hit_y))
			color = *(int *)(game->wall.tex_data + pixel_index);
		if (y >= 0 && y < HEIGHT)
			ft_mlx_pixel_put(game, x_start, y, color);
	}
	// Draw floor
	for (int i = y_start + wall_height; i < HEIGHT; i++)
		ft_mlx_pixel_put(game, x_start, i,  0x003E2A);
}

void cast_ray(t_game *game, double ray_angle, int i)
{
	t_ray	hor;
	t_ray	ver;
	hor.dst = INFINITY;
	hor.x = 0;
	hor.y = 0;
	hor.ray_angle = ray_angle;
	ver.dst = INFINITY;
	ver.x = 0;
	ver.y = 0;
	ver.ray_angle = ray_angle;
	hor_rays(game, &hor);
	vert_rays(game, &ver);
	game->wall.wall_cord = 0;
	game->wall.vert = 0;
	game->wall.hor = 0;
	double wall_height = 0;
	if (hor.dst < ver.dst)
	{
		wall_height = (BLOCK_SIZE / (hor.dst * cos(ray_angle - game->player.pva))) * ((WIDTH / 2) / tan(FOV_RAD / 2));
		game->wall.wall_cord = hor.x;
		game->wall_hit_x = hor.x;
		game->wall_hit_y = hor.y;
	}
	else
	{
		wall_height = (BLOCK_SIZE / (ver.dst * cos(ray_angle - game->player.pva))) * ((WIDTH / 2) / tan(FOV_RAD / 2));
		game->wall.wall_cord = ver.y;
		game->wall_hit_x = ver.x;
		game->wall_hit_y = ver.y;
	}
	draw_3d(game, i, (HEIGHT / 2) - (wall_height / game->view_height), wall_height);
}

double normalize_angle(double angle)
{
	double n_angle = fmod(angle, PI * 2);
	if (n_angle < 0)
		n_angle += PI * 2;
	return n_angle;
}

void cast_rays(t_game *game)
{
    double angle_step = FOV_RAD / WIDTH;
    double ray_angle = normalize_angle(game->player.pva - (FOV_RAD / 2));

    for (int i = 0; i < WIDTH; i++)
    {
        cast_ray(game, ray_angle, i);
        ray_angle = normalize_angle(ray_angle + angle_step);
    }
}
