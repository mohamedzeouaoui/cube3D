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
	// clean_screen(game);
	cast_rays(game);
	mlx_put_image_to_window(game->window.cnx, game->window.win, game->window.img.img, 0, 0);
}

void ft_mlx_init(t_game *game, t_data *data)
{
	game->wall_north.path = data->map_lines->line_NO;
	game->wall_south.path = data->map_lines->line_SO;
	game->wall_east.path = data->map_lines->line_EA;
	game->wall_west.path = data->map_lines->line_WE;
	game->window.cnx = mlx_init();
	game->window.win = mlx_new_window(game->window.cnx, WIDTH, HEIGHT, "cub3D");
	game->window.img.img = mlx_new_image(game->window.cnx, WIDTH, HEIGHT);
	//north
	game->wall_north.img = mlx_xpm_file_to_image(game->window.cnx, game->wall_north.path, &game->wall_north.width, &game->wall_north.height);
	if (!game->wall_north.img)
		exit(2);
	game->wall_north.tex_data = mlx_get_data_addr(game->wall_north.img, &game->wall_north.bpp, &game->wall_north.line_length, &game->wall_north.endian);
	// //south
	game->wall_south.img = mlx_xpm_file_to_image(game->window.cnx, game->wall_south.path, &game->wall_south.width, &game->wall_south.height);
	if (!game->wall_south.img)
		exit(2);
	game->wall_south.tex_data = mlx_get_data_addr(game->wall_south.img, &game->wall_south.bpp, &game->wall_south.line_length, &game->wall_south.endian);
	// //east
	game->wall_east.img = mlx_xpm_file_to_image(game->window.cnx, game->wall_east.path, &game->wall_east.width, &game->wall_east.height);
	if (!game->wall_east.img)
		exit(2);
	game->wall_east.tex_data = mlx_get_data_addr(game->wall_east.img, &game->wall_east.bpp, &game->wall_east.line_length, &game->wall_east.endian);
	// //west
	game->wall_west.img = mlx_xpm_file_to_image(game->window.cnx, game->wall_west.path, &game->wall_west.width, &game->wall_west.height);
	if (!game->wall_west.img)
		exit(2);
	game->wall_west.tex_data = mlx_get_data_addr(game->wall_west.img, &game->wall_west.bpp, &game->wall_west.line_length, &game->wall_west.endian);
	game->window.img.addr = mlx_get_data_addr(game->window.img.img, &game->window.img.bpp, &game->window.img.line_length, &game->window.img.endian);
}

void ft_mlx(t_game *game, t_data *data)
{
	ft_mlx_init(game, data);
	mlx_hook(game->window.win, 17, 0, ft_close, &game->window);
	mlx_loop_hook(game->window.cnx, drawer, game);
	mlx_hook(game->window.win, KeyPress, KeyPressMask, keys, game);
	mlx_loop(game->window.cnx);
}

void player_abilities(t_game *game, int i, int j)
{
	game->player.move_speed = 10;
	game->player.x = j;
	game->player.y = i;
	game->player.x_pixel = (j * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	game->player.y_pixel = (i * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	game->player.rotaion_speed = 3 * (PI / 180);
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