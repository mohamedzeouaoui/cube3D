#include "cub3d.h"

static size_t	get_map_rows(const char *file_name)
{
	int		fd;
	char	*line;
	size_t	rows;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_panic(file_name);
	rows = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		rows++;
		free(line);
	}
	close(fd);
	return (rows);
}

char	**parse_map(const char *file_name, t_game *game)
{
	int		fd;
	char	**map;
	size_t	rows;
	int	i;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		ft_panic(file_name);
	rows = get_map_rows(file_name);
	map = ft_calloc(rows + 1, sizeof(char *));
	if (!map)
		ft_panic("malloc");
	i = 0;
	while (i < rows)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	game->map_len = i - 1;
	close(fd);
	return (map);
}

int ft_close(t_window *window)
{
	mlx_destroy_window(window->cnx, window->win);
	mlx_destroy_display(window->cnx);
	exit(0);
}

void clean_screen(t_game *game)
{
	ft_memset(game->window.img.addr, 0, WIDTH * HEIGHT * sizeof(int));
}

int mouse_move_hook(int x, int y, void *game1)
{
	t_game *game = (t_game *)game1;
	static int last_x = -1;

	if (last_x == -1)
		last_x = x;
	if (x > last_x)
		game->player.pva = normalize_angle(game->player.pva + (game->player.rotaion_speed));
	else if (x < last_x)
		game->player.pva = normalize_angle(game->player.pva - (game->player.rotaion_speed));
	last_x = x;
	clean_screen(game);
	return (0);
}

int keys(int keycode, void *game1)
{
	int new_pos = 0;
	t_game *game = game1;
	if (keycode == 113 || 65307 == keycode)
		ft_close(&game->window);
	if (keycode == 65361)
		game->player.pva = normalize_angle(game->player.pva - (game->player.rotaion_speed));
	if (keycode == 65363)
		game->player.pva = normalize_angle(game->player.pva + (game->player.rotaion_speed));
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.forward = 0;
	game->keys.backward = 0;
	if (game->player.pva > (45 * (PI / 180)) && game->player.pva < (135 * (PI / 180)))
	{
		game->keys.left = 100;
		game->keys.right = 97;
		game->keys.forward = 115;
		game->keys.backward = 119;
	}
	else if (game->player.pva > (225 * (PI / 180)) && game->player.pva < (315 * (PI / 180)))
	{
		game->keys.left = 97;
		game->keys.right = 100;
		game->keys.forward = 119;
		game->keys.backward = 115;
	}
	else if (game->player.pva > (315 * (PI / 180)) || game->player.pva < (45 * (PI / 180)))
	{
		game->keys.left = 115;
		game->keys.right = 119;
		game->keys.forward = 97;
		game->keys.backward = 100;
	}
	else if (game->player.pva > (135 * (PI / 180)) && game->player.pva < (225 * (PI / 180)))
	{
		game->keys.left = 119;
		game->keys.right = 115;
		game->keys.forward = 100;
		game->keys.backward = 97;
	}
	if (keycode == game->keys.left)
	{
		new_pos = game->player.x_pixel - game->player.move_speed;
		if (!found_wall(game, new_pos, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
	if (keycode == game->keys.right)
	{
		new_pos = game->player.x_pixel + game->player.move_speed;
		if (!found_wall(game, new_pos, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
	if (keycode == game->keys.forward)
	{
		new_pos = game->player.y_pixel - game->player.move_speed;
		if (!found_wall(game, game->player.x_pixel, new_pos))
			game->player.y_pixel = new_pos;
	}
	if (keycode == game->keys.backward)
	{
		new_pos = game->player.y_pixel + game->player.move_speed;
		if (!found_wall(game, game->player.x_pixel, new_pos))
			game->player.y_pixel = new_pos;
	}
	clean_screen(game);
}

void	ft_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->window.img.addr + (y * game->window.img.line_length + x * (game->window.img.bpp / 8));
	*(unsigned int*)dst = color;
}

void draw_square(t_game *game, int x_start, int y_start, int color)
{
    int x;
    int y;

    y = y_start + 1;
    while (y < y_start + BLOCK_SIZE)
    {
        x = x_start + 1;
        while (x < x_start + BLOCK_SIZE)
        {
            ft_mlx_pixel_put(game, x, y, color);
            x++;
        }
        y++;
    }
}

int get_map_columns(char *name)
{
	int		fd;
	char	*line;
	int	size;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		ft_panic(name);
	line = get_next_line(fd);
	close(fd);
	return (ft_strlen(line));
}

void draw_horizontal_line(t_game *game, int x1, int x2, int y, int color)
{
    for (int x = x1; x <= x2; x++)
        ft_mlx_pixel_put(game, x, y, color);
}

void draw_circle(t_game *game, int color)
{
    int x = game->player.x_pixel;
    int y = game->player.y_pixel;
    int radius = 5;
    int x_pos = 0;
    int y_pos = radius;
    int decision = 1 - radius;

    draw_horizontal_line(game, x - radius, x + radius, y, color);
    while (y_pos >= x_pos)
    {
        draw_horizontal_line(game, x - x_pos, x + x_pos, y + y_pos, color);
        draw_horizontal_line(game, x - x_pos, x + x_pos, y - y_pos, color);
        draw_horizontal_line(game, x - y_pos, x + y_pos, y + x_pos, color);
        draw_horizontal_line(game, x - y_pos, x + y_pos, y - x_pos, color);

        if (decision <= 0)
            decision += 2 * x_pos + 5;
        else
        {
            decision += 2 * (x_pos - y_pos) + 5;
            y_pos--;
        }
        x_pos++;
    }
}

void draw_view_line(t_game *game)
{
    int x_start = game->player.x_pixel;
    int x_end = x_start + cos(game->player.pva) * 10;
    int y_start = game->player.y_pixel;
    int y_end = y_start + sin(game->player.pva) * 10;

    int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);
    int sx = x_start < x_end ? 1 : -1;
    int sy = y_start < y_end ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        ft_mlx_pixel_put(game, x_start, y_start, 0xff0000);
        if (x_start == x_end && y_start == y_end)
			break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x_start += sx; }
        if (e2 < dy) { err += dx; y_start += sy; }
    }
}

void draw_line(t_game *game, int x_end, int y_end)
{
	int x_start = game->player.x_pixel;
	int y_start = game->player.y_pixel;

	int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);
    int sx = x_start < x_end ? 1 : -1;
    int sy = y_start < y_end ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        ft_mlx_pixel_put(game, x_start, y_start, 0xff0000);
        if (x_start == x_end && y_start == y_end)
			break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x_start += sx; }
        if (e2 < dy) { err += dx; y_start += sy; }
	}
}

int found_wall(t_game *game, int x_pos, int y_pos)
{
	if (x_pos < 0 || x_pos > WIDTH || y_pos < 0 || y_pos > HEIGHT)
		return (1);
	int x_map = floor(x_pos / BLOCK_SIZE);
	int y_map = floor(y_pos / BLOCK_SIZE);
	if (y_map >= game->map_len || x_map > ft_strlen(game->map[y_map]))
		return (1);
	if (game->map[y_map][x_map] && game->map[y_map][x_map] == '1')
		return (1);
	return (0);
}

double count_distance(double x1, double x2, double y1, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

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
	while(y_next_step > 0 && x_next_step > 0 && x_next_step < WIDTH && y_next_step < HEIGHT)
	{
		if (found_wall(game, x_next_step, y_next_step))
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

	//vertical intersection -----------
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
	while(y_next_step > 0 && x_next_step > 0 && x_next_step < WIDTH && y_next_step < HEIGHT)
	{
		if (found_wall(game, x_next_step, y_next_step))
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

void draw_3d(t_game *game, int x_start, int y_start, int color, int wall_height)
{
	y_start = (HEIGHT / 2) - (wall_height / 2);
	for (int y = y_start; y < y_start + wall_height; y++)
	{
		if (y >= 0 && y < HEIGHT)
			ft_mlx_pixel_put(game, x_start, y, 0x808080);
	}
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

	double wall_height = 0;
	if (hor.dst < ver.dst)
	{
		wall_height = (BLOCK_SIZE / (hor.dst * cos(ray_angle - game->player.pva))) * ((WIDTH / 2) / tan(FOV_RAD / 2));
		// draw_line(game, hor.x, hor.y);
	}
	else
	{
		wall_height = (BLOCK_SIZE / (ver.dst * cos(ray_angle - game->player.pva))) * ((WIDTH / 2) / tan(FOV_RAD / 2));
		// draw_line(game, ver.x, ver.y);
	}
	draw_3d(game, i, (WIDTH / 2) - (wall_height / 2), 0xff0000, wall_height);
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
	double ray_angle = (game->player.pva - (FOV_RAD / 2)) + FOV_RAD / WIDTH;
	for (int i = 0; i < WIDTH; i++)
	{
		cast_ray(game, normalize_angle(ray_angle), i);
		ray_angle += FOV_RAD / WIDTH;
	}
}

void draw_map(t_game *game)
{
	char **map = game->map;
	int y = 0;
	int x;
	int x_offset = 0;
	int y_offset = 0;
	for (int i = 0; i < game->map_len + 1; i++)
	{
		y_offset = i * BLOCK_SIZE;
		for (int j = 0; j + 1 < ft_strlen(map[i]); j++)
		{
			x_offset = j * BLOCK_SIZE;
			int color = 0xffffff;
			if (map[i][j] == '1')
				color = 0x0000f0;
			// draw_square(game, x_offset, y_offset, color);
			// draw_circle(game, 0xff0000);
			// draw_view_line(game);
			cast_rays(game);
		}
	}
	mlx_put_image_to_window(game->window.cnx, game->window.win, game->window.img.img, 0, 0);
}

int drawer(t_game *game)
{
	draw_map(game);
	return (0);
}

void ft_mlx(t_game *game)
{
	game->window.cnx = mlx_init();
	game->window.win = mlx_new_window(game->window.cnx, WIDTH, HEIGHT, "cub3D");
	game->window.img.img = mlx_new_image(game->window.cnx, WIDTH, HEIGHT);
	game->window.img.addr = mlx_get_data_addr(game->window.img.img, &game->window.img.bpp, &game->window.img.line_length, &game->window.img.endian);
	mlx_hook(game->window.win, 17, 0, ft_close, &game->window);
	mlx_loop_hook(game->window.cnx, drawer, game);
	mlx_hook(game->window.win, 6, 1L << 6, mouse_move_hook, game);
	mlx_hook(game->window.win, KeyPress, KeyPressMask, keys, game);
	mlx_loop(game->window.cnx);
}

void find_player(t_game *game)
{
	game->player.move_speed = 5;
	for(int i = 0; i < game->map_len + 1; i++)
	{
		for (int j = 0; j < ft_strlen(game->map[i]); j++)
		{
			if (game->map[i][j] == 'N')
			{
				game->player.pva = -(PI / 2);
				game->player.x_pixel = (j * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.y_pixel = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.rotaion_speed = 1.5 * (PI / 180);
				return ;
			}
		}
	}
}

void setup(t_game *game, int ac, char **av)
{
    if (ac != 2)
		exit(ft_error(CUB3D_USAGE));
	if (ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		exit(ft_error(ERR_INVALID_FILENAME));
	game->map = parse_map(av[1], game);
	game->filename = av[1];
	find_player(game);
	ft_mlx(game);
}

// -lmlx -lX11 -lXext -lm -Llibft -lft