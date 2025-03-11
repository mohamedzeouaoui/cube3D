#include "../cub3d.h"

void hor_rays2(t_game *game, t_ray *hor)
{
	hor->x_next_step = hor->x_intercept;
	hor->y_next_step = hor->y_intercept;

	if (!hor->is_ray_facing_down)
		hor->y_next_step -= 0.001;
	
	while(1)
	{
		if (found_wall(game, hor->x_next_step, hor->y_next_step) || 
			found_door(game, hor->x_next_step, hor->y_next_step))
		{
			hor->dst = count_distance(game->player.x_pixel, hor->x_next_step, 
									 game->player.y_pixel, hor->y_next_step);
			hor->x = hor->x_next_step;
			hor->y = hor->y_next_step;
			return;
		}
		hor->x_next_step += hor->x_step;
		hor->y_next_step += hor->y_step;
	}
	
	hor->dst = INFINITY;
}

void hor_rays(t_game *game, t_ray *hor)
{
	hor->is_ray_facing_down = (hor->ray_angle > 0 && hor->ray_angle < PI);
	hor->is_ray_facing_right = (hor->ray_angle < (0.5 * PI) || hor->ray_angle > (PI * 1.5));

	hor->y_intercept = floor(game->player.y_pixel / BLOCK_SIZE) * BLOCK_SIZE;
	if (hor->is_ray_facing_down)
		hor->y_intercept += BLOCK_SIZE;
	hor->x_intercept = game->player.x_pixel + ((hor->y_intercept - game->player.y_pixel) / tan(hor->ray_angle));

	hor->y_step = hor->is_ray_facing_down ? BLOCK_SIZE : -BLOCK_SIZE;
	hor->x_step = BLOCK_SIZE / tan(hor->ray_angle);
	if ((!hor->is_ray_facing_right && hor->x_step > 0) || (hor->is_ray_facing_right && hor->x_step < 0))
		hor->x_step *= -1;

	hor_rays2(game, hor);
}

void vert_rays2(t_game *game, t_ray *ver)
{
	ver->x_next_step = ver->x_intercept;
	ver->y_next_step = ver->y_intercept;
	
	if (!ver->is_ray_facing_right)
		ver->x_next_step -= 0.001;

	while(ver->x_next_step >= 0 && ver->x_next_step <= game->map_width * BLOCK_SIZE &&
		  ver->y_next_step >= 0 && ver->y_next_step <= game->map_len * BLOCK_SIZE)
	{
		if (found_wall(game, ver->x_next_step, ver->y_next_step) || 
			found_door(game, ver->x_next_step, ver->y_next_step))
		{
			ver->dst = count_distance(game->player.x_pixel, ver->x_next_step, 
									 game->player.y_pixel, ver->y_next_step);
			ver->x = ver->x_next_step;
			ver->y = ver->y_next_step;
			break;
		}
		ver->x_next_step += ver->x_step;
		ver->y_next_step += ver->y_step;
		if (ver->x_next_step < 0 || ver->x_next_step > game->map_width * BLOCK_SIZE ||
			ver->y_next_step < 0 || ver->y_next_step > game->map_len * BLOCK_SIZE)
			break;
	}
	if (ver->dst == INFINITY)
	{
		ver->dst = count_distance(game->player.x_pixel, ver->x_next_step, 
								  game->player.y_pixel, ver->y_next_step);
		ver->x = ver->x_next_step;
		ver->y = ver->y_next_step;
	}
}

void vert_rays(t_game *game, t_ray *ver)
{
	ver->is_ray_facing_down = (ver->ray_angle > 0 && ver->ray_angle < PI);
	ver->is_ray_facing_right = (ver->ray_angle < (0.5 * PI) || ver->ray_angle > (PI * 1.5));

	ver->x_intercept = floor(game->player.x_pixel / BLOCK_SIZE) * BLOCK_SIZE;
	if (ver->is_ray_facing_right)
		ver->x_intercept += BLOCK_SIZE;
	ver->y_intercept = game->player.y_pixel + ((ver->x_intercept - game->player.x_pixel) * tan(ver->ray_angle));

	ver->x_step = ver->is_ray_facing_right ? BLOCK_SIZE : -BLOCK_SIZE;
	ver->y_step = BLOCK_SIZE * tan(ver->ray_angle);
	if ((!ver->is_ray_facing_down && ver->y_step > 0) || (ver->is_ray_facing_down && ver->y_step < 0))
		ver->y_step *= -1;

	vert_rays2(game, ver);
}

void cast_ray_init(t_game *game, t_ray *hor, t_ray *ver, double ray_angle)
{
	hor->dst = INFINITY;
	hor->x = 0;
	hor->y = 0;
	hor->ray_angle = ray_angle;
	ver->dst = INFINITY;
	ver->x = 0;
	ver->y = 0;
	ver->ray_angle = ray_angle;
	game->which_hit = -1;
	game->wall.wall_cord = 0;
	game->wall.vert = 0;
	game->wall.hor = 0;
	game->wall_height = 0;
}

void cast_ray(t_game *game, double ray_angle, int i)
{
	t_ray hor, ver;
	cast_ray_init(game, &hor, &ver, ray_angle);
	hor_rays(game, &hor);
	vert_rays(game, &ver);

	double cos_angle_diff = cos(ray_angle - game->player.pva);
	double wall_height_factor = (WIDTH / 2) / tan(FOV_RAD / 2);

	if (hor.dst < ver.dst)
	{
		game->wall_height = (BLOCK_SIZE / (hor.dst * cos_angle_diff)) * wall_height_factor;
		game->wall.wall_cord = fmod(hor.x, BLOCK_SIZE);
		game->wall_hit_x = hor.x;
		game->wall_hit_y = hor.y;
		game->which_hit = 1;
	}
	else
	{
		game->wall_height = (BLOCK_SIZE / (ver.dst * cos_angle_diff)) * wall_height_factor;
		game->wall.wall_cord = fmod(ver.y, BLOCK_SIZE);
		game->wall_hit_x = ver.x;
		game->wall_hit_y = ver.y;
		game->which_hit = 0;
	}
	draw_3d(game, i, (HEIGHT / 2) - (game->wall_height / game->view_height), game->wall_height, ray_angle);
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
