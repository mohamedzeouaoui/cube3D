#include "../cub3d.h"

int found_wall(t_game *game, int x_pos, int y_pos)
{
    if (x_pos < 0 || x_pos >= (game->map_width * BLOCK_SIZE) || y_pos < 0 || y_pos >= (game->map_len * BLOCK_SIZE))
        return (1);

    int x_map = x_pos / BLOCK_SIZE;
    int y_map = y_pos / BLOCK_SIZE;

    return (game->map[y_map][x_map] == '1');
}

double count_distance(double x1, double x2, double y1, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int r_g_b(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

double normalize_angle(double angle)
{
	double n_angle = fmod(angle, PI * 2);
	if (n_angle < 0)
		n_angle += PI * 2;
	return n_angle;
}

void draw_ceiling(t_game *game, int y_start, int x_start)
{
	int i = 0;
	while(i < y_start)
	{
		ft_mlx_pixel_put(game, x_start, i, game->c_color);
		i++;
	}
}

void draw_floor(t_game *game, int y_start, int x_start, int wall_height)
{
	int i = y_start + wall_height;
	while(i < HEIGHT)
	{
		ft_mlx_pixel_put(game, x_start, i, game->f_color);
		i++;
	}
}

int ray_facing_north(double ray_angle)
{
    ray_angle = normalize_angle(ray_angle);
    return (ray_angle > PI && ray_angle < 1.5 * PI);
}

int ray_facing_south(double ray_angle)
{
    ray_angle = normalize_angle(ray_angle);
    return (ray_angle > 0.5 * PI && ray_angle < PI);
}

int ray_facing_east(double ray_angle)
{
    ray_angle = normalize_angle(ray_angle);
    return (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI);
}

int ray_facing_west(double ray_angle)
{
    ray_angle = normalize_angle(ray_angle);
    return (ray_angle > 0.5 * PI);
}
