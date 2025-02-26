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

char **parse_map(const char *file_name, t_game *game)
{
    int fd;
    char **map;
    char *line;
    size_t rows = 0;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        ft_panic(file_name);

    map = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        map = realloc(map, sizeof(char *) * (rows + 2));
        if (!map)
            ft_panic("malloc");
        map[rows++] = line;
    }
    map[rows] = NULL;
    game->map_len = rows;
    close(fd);
    return map;
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
	game->player.direction = 0;
	if (game->player.pva > (45 * (PI / 180)) && game->player.pva < (135 * (PI / 180)))
	{
		game->keys.left = 100;
		game->keys.right = 97;
		game->keys.forward = 115;
		game->keys.backward = 119;
		game->player.direction = 2;
	}
	else if (game->player.pva > (225 * (PI / 180)) && game->player.pva < (315 * (PI / 180)))
	{
		game->keys.left = 97;
		game->keys.right = 100;
		game->keys.forward = 119;
		game->keys.backward = 115;
		game->player.direction = 0;
	}
	else if (game->player.pva > (315 * (PI / 180)) || game->player.pva < (45 * (PI / 180)))
	{
		game->keys.left = 115;
		game->keys.right = 119;
		game->keys.forward = 97;
		game->keys.backward = 100;
		game->player.direction = 1;
	}
	else if (game->player.pva > (135 * (PI / 180)) && game->player.pva < (225 * (PI / 180)))
	{
		game->keys.left = 119;
		game->keys.right = 115;
		game->keys.forward = 100;
		game->keys.backward = 97;
		game->player.direction = 3;
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
    int y = 0;

    y = y_start + 1;
    while (y < HEIGHT && y < y_start + BLOCK_SIZE)
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
    int x = game->player.x_pixel / BLOCK_SIZE;
    int y = game->player.y_pixel / BLOCK_SIZE;
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
    if (x_pos < 0 || x_pos >= (game->map_width * BLOCK_SIZE) || y_pos < 0 || y_pos >= (game->map_len * BLOCK_SIZE))
        return (1);

    int x_map = x_pos / BLOCK_SIZE;
    int y_map = y_pos / BLOCK_SIZE;

    if (y_map >= game->map_len || x_map >= game->map_width)
        return (1);
    return (game->map[y_map][x_map] == '1');
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
	while(1)
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
	while(y_next_step > 0 && x_next_step > 0)
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

// void draw_3d(t_game *game, int x_start, int y_start, int wall_height)
// {
// 	int tex_cord = game->wall.wall_cord * BLOCK_SIZE;
// 	y_start = (HEIGHT / 2) - (wall_height / 2);
// 	for (int y = y_start; y < y_start + wall_height; y++)
// 	{
// 		if (y >= 0 && y < HEIGHT)
// 			ft_mlx_pixel_put(game, x_start, y, 0x808080);
// 	}
// }

unsigned int	my_mlx_pixel_get(t_game *game, int x, int y)
{
	char	*dst;

	dst = game->wall.addr + (y * game->wall.line_length + x * (game->wall.bpp / 8));
	return (*(unsigned int *)dst);
}


void draw_3d(t_game *game, int x_start, int y_start, int wall_height)
{
	int y = 0;
	int tex_x = (int)(game->wall.wall_cord * BLOCK_SIZE) % BLOCK_SIZE; // Get texture column
	double step = 1.0 * BLOCK_SIZE / wall_height;
	double tex_pos = 0;

	// y_start = (HEIGHT / 2) - (wall_height / game->view_height);
	// Draw ceiling
	for (int i = 0; i < y_start; i++)
		ft_mlx_pixel_put(game, x_start, i, 0xff0000);
	for (y = y_start; y < y_start + wall_height; y++)
	{
		int tex_y = (int)tex_pos; // Keep within texture bounds
		tex_pos += step;

		// Get pixel color from texture
		int pixel_index = (tex_y * game->wall.line_length) + (tex_x * (game->wall.bpp / 8));
		int color = *(int *)(game->wall.tex_data + pixel_index);
		if (y >= 0 && y < HEIGHT)
			ft_mlx_pixel_put(game, x_start, y, color);
	}
	// Draw floor
	for (int i = y_start + wall_height; i < HEIGHT; i++)
		ft_mlx_pixel_put(game, x_start, i, 0x00ff00);
}

// width scaling
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
		game->wall.wall_cord = hor.x - floor(hor.x);
		// game->wall.hor = 1;
	}
	else
	{
		wall_height = (BLOCK_SIZE / (ver.dst * cos(ray_angle - game->player.pva))) * ((WIDTH / 2) / tan(FOV_RAD / 2));
		game->wall.wall_cord = ver.y - floor(ver.y);
		// game->wall.vert = 1;
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

void draw_2d_map(t_game *game)
{
	int map_x, map_y;
	int x_start, y_start;
	int color;

	for (map_y = 0; map_y < game->map_len; map_y++)
	{

		for (map_x = 0; map_x < game->map_width; map_x++)
		{
			x_start = WIDTH - (game->map_width * BLOCK_SIZE / 2) + (map_x * BLOCK_SIZE / 2);
			y_start = map_y * BLOCK_SIZE / 2;
			if (game->map[map_y][map_x] == '1')
				color = 0xFFFFFF; // White for walls
			else if (game->map[map_y][map_x] == '0')
				color = 0x000000; // Black for empty spaces
			else if (game->map[map_y][map_x] == 'E')
				color = 0xFF0000; // Red for player start position
			else
				color = 0x000000; // Default to black for any other characters

			// draw_square(game, x_start, y_start, color);
		}
	}

	// Draw player position
	int player_x = WIDTH - (game->map_width * BLOCK_SIZE / 2) + (game->player.x * BLOCK_SIZE / 2) + (BLOCK_SIZE / 4);
	int player_y = (game->player.y * BLOCK_SIZE) + (BLOCK_SIZE / 4);
	// draw_circle(game, 0x00FF00); // Green for player position
}

void draw_mini_map_content(t_game *game, int y, int x)
{
    int x_start;
    int y_start = 0;
	int x_offset = 0;
	int y_offset = 0;

    y_start = y - 1;
    while (y_start < y + 1)
    {
        x = x_start - 1;
        while (x_start < x + 1)
        {

			// if (game->map[y_start][x_start] == '1')
			
	        // ft_mlx_pixel_put(game, x, y, 0x00ffff);
			// else
				// ft_mlx_pixel_put(game, x, y, 0x000000);
            x_start++;
        }
        y_start++;
    }
}

void square(t_game *game, int x_start, int y_start, int color)
{
	for (int i = y_start; i < 20; i++)
	{
		for (int j = x_start; j < 20; j++)
		{
			ft_mlx_pixel_put(game, j, i, color);
		}
	}
}

void draw_square2(t_game *game, int x_start, int y_start, int color, int f)
{
	if (f == 0)
	{
		for (int y = y_start; y < y_start + 20; y++)
		{
			for (int x = x_start; x < x_start + 20; x++)
			{
				ft_mlx_pixel_put(game, x, y, color);
			}
		}
	}
	else
	{
		for (int y = y_start; y < y_start + 8; y++)
		{
			for (int x = x_start; x < x_start + 8; x++)
			{
				ft_mlx_pixel_put(game, x + 5, y + 5, color);
			}
		}
	}
}

void draw_circle2(t_game *game, int x_start, int y_start, int color)
{
	int x = 5;
    int y = 5;
    int radius = 5;
    int x_pos = 0;
    int y_pos = radius;
    int decision = 1 - radius;

    draw_horizontal_line(game, x - radius, x + radius, y, color);
    // while (y_pos >= x_pos)
    // {
    //     draw_horizontal_line(game, x - x_pos, x + x_pos, y + y_pos, color);
    //     draw_horizontal_line(game, x - x_pos, x + x_pos, y - y_pos, color);
    //     draw_horizontal_line(game, x - y_pos, x + y_pos, y + x_pos, color);
    //     draw_horizontal_line(game, x - y_pos, x + y_pos, y - x_pos, color);

    //     if (decision <= 0)
    //         decision += 2 * x_pos + 5;
    //     else
    //     {
    //         decision += 2 * (x_pos - y_pos) + 5;
    //         y_pos--;
    //     }
    //     x_pos++;
    // }
}

void draw_arrow(t_game *game, int x, int y, int color, int size)
{
    // Set default size if not specified
    if (size <= 0)
        size = 6;

	x += 8;
	y += 5;
    // Common variables for all arrow types
    int i, j;
    int outline_color = 0x000000; // Black outline

    // Draw  arrow shapes based on direction
    if (game->player.direction == 0) // Upward arrow (▲)
    {
        // Draw filled triangle
        for (i = -size; i <= size; i++)
        {
            for (j = 0; j <= size; j++)
            {
                // Calculate the position relative to the triangle's shape
                if (j <= size - abs(i))
                {
                    ft_mlx_pixel_put(game, x + i, y - j, color);
                }
            }
        }

        // Draw outline
        for (i = -size; i <= size; i++)
        {
            // Bottom line
            if (i > -size && i < size)
                ft_mlx_pixel_put(game, x + i, y, outline_color);
            
            // Left diagonal
            j = abs(i + size);
            if (j <= size)
                ft_mlx_pixel_put(game, x - size + j, y - j, outline_color);
            
            // Right diagonal
            j = abs(i - size);
            if (j <= size)
                ft_mlx_pixel_put(game, x + size - j, y - j, outline_color);
        }
    }
    else if (game->player.direction == 1) // Rightward arrow (▶)
    {
        // Draw filled triangle
        for (i = 0; i <= size; i++)
        {
            for (j = -size; j <= size; j++)
            {
                if (i <= size - abs(j))
                {
                    ft_mlx_pixel_put(game, x + i, y + j, color);
                }
            }
        }

        // Draw outline
        for (j = -size; j <= size; j++)
        {
            // Left line
            if (j > -size && j < size)
                ft_mlx_pixel_put(game, x, y + j, outline_color);
            
            // Top diagonal
            i = abs(j + size);
            if (i <= size)
                ft_mlx_pixel_put(game, x + i, y - size + i, outline_color);
            
            // Bottom diagonal
            i = abs(j - size);
            if (i <= size)
                ft_mlx_pixel_put(game, x + i, y + size - i, outline_color);
        }
    }
    else if (game->player.direction == 2) // Downward arrow (▼)
    {
        // Draw filled triangle
        for (i = -size; i <= size; i++)
        {
            for (j = 0; j <= size; j++)
            {
                if (j <= size - abs(i))
                {
                    ft_mlx_pixel_put(game, x + i, y + j, color);
                }
            }
        }

        // Draw outline
        for (i = -size; i <= size; i++)
        {
            // Top line
            if (i > -size && i < size)
                ft_mlx_pixel_put(game, x + i, y, outline_color);
            
            // Left diagonal
            j = abs(i + size);
            if (j <= size)
                ft_mlx_pixel_put(game, x - size + j, y + j, outline_color);
            
            // Right diagonal
            j = abs(i - size);
            if (j <= size)
                ft_mlx_pixel_put(game, x + size - j, y + j, outline_color);
        }
    }
    else if (game->player.direction == 3) // Leftward arrow (◀)
    {
        // Draw filled triangle
        for (i = 0; i <= size; i++)
        {
            for (j = -size; j <= size; j++)
            {
                if (i <= size - abs(j))
                {
                    ft_mlx_pixel_put(game, x - i, y + j, color);
                }
            }
        }

        // Draw outline
        for (j = -size; j <= size; j++)
        {
            // Right line
            if (j > -size && j < size)
                ft_mlx_pixel_put(game, x, y + j, outline_color);
            
            // Top diagonal
            i = abs(j + size);
            if (i <= size)
                ft_mlx_pixel_put(game, x - i, y - size + i, outline_color);
            
            // Bottom diagonal
            i = abs(j - size);
            if (i <= size)
                ft_mlx_pixel_put(game, x - i, y + size - i, outline_color);
        }
    }
}



void draw_mini_map(t_game *game)
{
	int player_x = game->player.x_pixel / BLOCK_SIZE;
	int player_y = game->player.y_pixel / BLOCK_SIZE;
	int x_start, y_start, x_off, y_off;
	int mini_map_width = 10;
	int mini_map_height = 10; 

	y_off = 0;
	for(int k = 0; k < mini_map_height; k++)
	{
		for (int l = 0; l < mini_map_width; l++)
			draw_square2(game, l * 20, k * 20, 0x000000, 0);
	}
	for (int y = player_y - mini_map_height / 2; y < player_y + mini_map_height / 2; y++)
	{
		x_off = 0;
		for (int x = player_x - mini_map_width / 2; x < player_x + mini_map_width / 2; x++)
		{
			if (y >= 0 && y < game->map_len && x >= 0 && x < game->map_width)
			{
				if (game->map[y][x] == '1')
					draw_square2(game, x_off, y_off, 0x00FFFF, 0); // Wall
				else if (game->map[y][x] == '0' || game->map[y][x] == 'S')
					draw_square2(game, x_off, y_off, 0x000000, 0); // Floor
			}
			x_off += 20;
		}
		y_off += 20;
	}

	// Draw player position
	// draw_circle2(game, x_off, y_off, 0xFF0000);
	// draw_square2(game, (mini_map_width / 2) * 20, (mini_map_height / 2) * 20, 0xFF0000, 1);
	draw_arrow(game, (mini_map_width / 2) * 20, (mini_map_height / 2) * 20, 0xFF0000, 0);
}


void draw_map(t_game *game)
{
	char **map = game->map;

	clean_screen(game);
	cast_rays(game);
	draw_mini_map(game);
	// draw_2d_map(game);
	mlx_put_image_to_window(game->window.cnx, game->window.win, game->window.img.img, 0, 0);
}

int drawer(t_game *game)
{
	draw_map(game);
	return (0);
}

int crouch(int keycode, void *game1)
{
	static int f;
	t_game *game = (t_game *)game1;
	if (keycode == 65507)
	{
		if (f == 1)
		{
			f = 0;
			game->view_height = 2.5;
			game->player.move_speed = 5;//normal
		}
		else
		{
			f = 1;
			game->view_height = 1.5;
			game->player.move_speed = 5 / 2;
		}
	}
}

void ft_mlx(t_game *game)
{
	game->window.cnx = mlx_init();
	game->window.win = mlx_new_window(game->window.cnx, WIDTH, HEIGHT, "cub3D");
	game->window.img.img = mlx_new_image(game->window.cnx, WIDTH, HEIGHT);
	game->wall.img = mlx_xpm_file_to_image(game->window.cnx, game->wall.path, &game->wall.width, &game->wall.height);
	if (!game->wall.img)
		exit(2);
	game->wall.tex_data = mlx_get_data_addr(game->wall.img, &game->wall.bpp, &game->wall.line_length, &game->wall.endian);
	game->window.img.addr = mlx_get_data_addr(game->window.img.img, &game->window.img.bpp, &game->window.img.line_length, &game->window.img.endian);
	mlx_hook(game->window.win, 17, 0, ft_close, &game->window);
	mlx_loop_hook(game->window.cnx, drawer, game);
	mlx_hook(game->window.win, KeyPress, KeyPressMask, crouch, game);
	mlx_hook(game->window.win, KeyRelease, KeyReleaseMask, crouch, game);
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
				game->player.x = j;
				game->player.y = i;
				game->player.x_pixel = (j * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.y_pixel = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.rotaion_speed = 1.5 * (PI / 180);
				game->player.direction = 0;
				return ;
			}
			else if (game->map[i][j] == 'S')
			{
				game->player.pva = (PI / 2);
				game->player.x = j;
				game->player.y = i;
				game->player.x_pixel = (j * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.y_pixel = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.rotaion_speed = 1.5 * (PI / 180);
				game->player.direction = 2;
				return ;
			}
			else if (game->map[i][j] == 'E')
			{
				game->player.pva = 0;
				game->player.x = j;
				game->player.y = i;
				game->player.x_pixel = (j * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.y_pixel = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.rotaion_speed = 1.5 * (PI / 180);
				game->player.direction = 1;
				return ;
			}
			else if (game->map[i][j] == 'W')
			{
				game->player.pva = PI;
				game->player.x = j;
				game->player.y = i;
				game->player.x_pixel = (j * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.y_pixel = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
				game->player.rotaion_speed = 1.5 * (PI / 180);
				game->player.direction = 3;
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
	game->map_width = ft_strlen(game->map[0]);
	game->filename = av[1];
	game->wall.path = ft_strdup("wall.xpm");
	game->view_height = 2.5;
	find_player(game);
	ft_mlx(game);
}

// -lmlx -lX11 -lXext -lm -Llibft -lft