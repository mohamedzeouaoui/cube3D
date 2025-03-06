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

void clean_screen(t_game *game)
{
	// ft_memset(game->window.img.addr, 0, WIDTH * HEIGHT * sizeof(int));
}

void	ft_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->window.img.addr + (y * game->window.img.line_length + x * (game->window.img.bpp / 8));
	*(unsigned int*)dst = color;
}

void draw_map(t_game *game)
{
	clean_screen(game);
	cast_rays(game);
	draw_mini_map(game);
	if (game->menu.started)
		mlx_put_image_to_window(game->window.cnx, game->window.win, game->window.img.img, 0, 0);
}

void draw_menu(t_game *game)
{
	if (game->menu.index == 0)
	{
		mlx_string_put(game->window.cnx, game->window.win, WIDTH / 2, HEIGHT / 3, 0x00ff00, "start game");
		mlx_string_put(game->window.cnx, game->window.win, WIDTH / 2, HEIGHT / 2, 0xffffff, "quit game");
	}
	else if (game->menu.index)
	{
		mlx_string_put(game->window.cnx, game->window.win, WIDTH / 2, HEIGHT / 3, 0xffffff, "start game");
		mlx_string_put(game->window.cnx, game->window.win, WIDTH / 2, HEIGHT / 2, 0xff0000, "quit game");
	}
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

void ft_mlx_init(t_game *game)
{
	game->window.cnx = mlx_init();
	game->window.win = mlx_new_window(game->window.cnx, WIDTH, HEIGHT, "cub3D");
	game->window.img.img = mlx_new_image(game->window.cnx, WIDTH, HEIGHT);
	game->wall.img = mlx_xpm_file_to_image(game->window.cnx, game->wall.path, &game->wall.width, &game->wall.height);
	if (!game->wall.img)
		exit(2);
	game->wall.tex_data = mlx_get_data_addr(game->wall.img, &game->wall.bpp, &game->wall.line_length, &game->wall.endian);
	game->menu.menu_img.img = mlx_xpm_file_to_image(game->window.cnx, game->menu.menu_img.path, &game->menu.menu_img.width, &game->menu.menu_img.height);
	if (!game->menu.menu_img.img)
		exit(2);
	game->menu.menu_img.tex_data = mlx_get_data_addr(game->menu.menu_img.img, &game->menu.menu_img.bpp, &game->menu.menu_img.line_length, &game->menu.menu_img.endian);
	game->door.img = mlx_xpm_file_to_image(game->window.cnx, game->door.path, &game->door.width, &game->door.height);
	if (!game->door.img)
		exit(2);
	game->door.tex_data = mlx_get_data_addr(game->door.img, &game->door.bpp, &game->door.line_length, &game->door.endian);
	game->window.img.addr = mlx_get_data_addr(game->window.img.img, &game->window.img.bpp, &game->window.img.line_length, &game->window.img.endian);
}

void ft_mlx(t_game *game)
{
	ft_mlx_init(game);
	mlx_hook(game->window.win, 17, 0, ft_close, &game->window);
	mlx_loop_hook(game->window.cnx, drawer, game);
	// mlx_hook(game->window.win, KeyPress, KeyPressMask, crouch, game);
	// mlx_hook(game->window.win, KeyRelease, KeyReleaseMask, crouch, game);
	mlx_hook(game->window.win, 6, 1L << 6, mouse_move_hook, game);
	mlx_key_hook(game->window.win, doors, game);
	mlx_hook(game->window.win, KeyPress, KeyPressMask, keys, game);
	mlx_loop(game->window.cnx);
}

void player_abilities(t_game *game, int i, int j)
{
	game->player.move_speed = 5;
	game->player.x = j;
	game->player.y = i;
	game->player.x_pixel = (j * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	game->player.y_pixel = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	game->player.rotaion_speed = 2 * (PI / 180);
}

void find_player(t_game *game)
{
	for(int i = 0; i < game->map_len + 1; i++)
	{
		for (int j = 0; j < ft_strlen(game->map[i]); j++)
		{
			if (game->map[i][j] == 'N')
			{
				game->player.pva = -(PI / 2);
				player_abilities(game, i, j);
				game->player.direction = 0;
				return ;
			}
			else if (game->map[i][j] == 'S')
			{
				game->player.pva = (PI / 2);
				player_abilities(game, i, j);
				game->player.direction = 2;
				return ;
			}
			else if (game->map[i][j] == 'E')
			{
				game->player.pva = 0;
				player_abilities(game, i, j);
				game->player.direction = 1;
				return ;
			}
			else if (game->map[i][j] == 'W')
			{
				game->player.pva = PI;
				player_abilities(game, i, j);
				game->player.direction = 3;
				return ;
			}
		}
	}
}
// -lmlx -lX11 -lXext -lm -Llibft -lft