#include "cub3d.h"

int ft_close(t_window *window)
{
	mlx_destroy_window(window->cnx, window->win);
	mlx_destroy_display(window->cnx);
	exit(0);
}

int drawer(t_game *game)
{
	if (game->menu.started)
		draw_map(game);
	else if (game->menu.ended)
		exit(0);
	else
	{
		//menu
		mlx_put_image_to_window(game->window.cnx, game->window.win, game->menu.menu_img.img, 0, 0);
		draw_menu(game);
		if (game->menu.index == 0 && game->menu.entred)
			game->menu.started = 1;
		if (game->menu.index == 1 && game->menu.entred)
			exit(0);
	}
	return (0);
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
	return (0);
}

int doors(int keycode, t_game *game)
{
	if (keycode == (int)'e')
	{
		// if (game->player.pva)
		int y = game->player.y_pixel / BLOCK_SIZE;
		int x = game->player.x_pixel / BLOCK_SIZE;
		if (facing_south(game) && game->map[y + 1][x] == 'C')
			game->map[y + 1][x] = 'O';
		else if (facing_north(game) && game->map[y - 1][x] == 'C')
			game->map[y - 1][x] = 'O';
		else if (facing_east(game) && game->map[y][x + 1] == 'C')
			game->map[y][x + 1] = 'O';
		else if (facing_west(game) && game->map[y][x - 1] == 'C')
			game->map[y][x - 1] = 'O';
		else if (facing_south(game) && game->map[y + 1][x] == 'O')
			game->map[y + 1][x] = 'C';
		else if (facing_north(game) && game->map[y - 1][x] == 'O')
			game->map[y - 1][x] = 'C';
		else if (facing_east(game) && game->map[y][x + 1] == 'O')
			game->map[y][x + 1] = 'C';
		else if (facing_west(game) && game->map[y][x - 1] == 'O')
			game->map[y][x - 1] = 'C';
	}
}

int keys(int keycode, void *game1)
{
	int new_pos = 0;
	float slide_amount = 0;
	t_game *game = game1;
	game->menu.entred = 0;
	if (keycode == 65362)
		game->menu.index = (game->menu.index + 1) % 2;
	else if (keycode == 65364)
		game->menu.index = (game->menu.index + 1) % 2;
	if (keycode == 65293)
		game->menu.entred = 1;
	if (keycode == 113 || 65307 == keycode)
	{
		// clean_screen(game);
		// game->menu.started = 0;
		ft_close(&game->window);
	}
	if (!game->menu.started)
		return 0;
	if (keycode == 65361)
		game->player.pva = normalize_angle(game->player.pva - (game->player.rotaion_speed));
	if (keycode == 65363)
		game->player.pva = normalize_angle(game->player.pva + (game->player.rotaion_speed));
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.forward = 0;
	game->keys.backward = 0;
	game->player.direction = 0;
	if (facing_south(game))//south
	{
		game->keys.left = 100;
		game->keys.right = 97;
		game->keys.forward = 115;
		game->keys.backward = 119;
		game->player.direction = 2;
	}
	else if (facing_north(game))//north
	{
		game->keys.left = 97;
		game->keys.right = 100;
		game->keys.forward = 119;
		game->keys.backward = 115;
		game->player.direction = 0;
	}
	else if (facing_east(game))//east ->
	{
		game->keys.left = 115;
		game->keys.right = 119;
		game->keys.forward = 97;
		game->keys.backward = 100;
		game->player.direction = 1;
	}
	else if (facing_west(game))//west <-
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
		if (!found_wall(game, new_pos, game->player.y_pixel) && !found_door(game, new_pos, game->player.y_pixel))
			game->player.x_pixel = new_pos;
		else
		{
			slide_amount = game->player.move_speed * sinf(game->player.pva);
			new_pos = game->player.y_pixel + slide_amount;
			if (!found_wall(game, game->player.x_pixel, new_pos) && !found_door(game, game->player.x_pixel, new_pos))
				game->player.y_pixel = new_pos;
		}
	}
	if (keycode == game->keys.right)
	{
		new_pos = game->player.x_pixel + game->player.move_speed;
		if (!found_wall(game, new_pos, game->player.y_pixel) && !found_door(game, new_pos, game->player.y_pixel))
			game->player.x_pixel = new_pos;
		else
		{
			slide_amount = game->player.move_speed * sinf(game->player.pva);
			new_pos = game->player.y_pixel + slide_amount;
			if (!found_wall(game, game->player.x_pixel, new_pos) && !found_door(game, game->player.x_pixel, new_pos))
				game->player.y_pixel = new_pos;
		}
	}
	if (keycode == game->keys.forward)
	{
		new_pos = game->player.y_pixel - game->player.move_speed;
		if (!found_wall(game, game->player.x_pixel, new_pos) && !found_door(game, game->player.x_pixel, new_pos))
			game->player.y_pixel = new_pos;
		else
		{
			slide_amount = game->player.move_speed * cosf(game->player.pva);
			new_pos = game->player.x_pixel + slide_amount;
			if (!found_wall(game, new_pos, game->player.y_pixel) && !found_door(game, new_pos, game->player.y_pixel))
				game->player.x_pixel = new_pos;
		}
	}
	if (keycode == game->keys.backward)
	{
		new_pos = game->player.y_pixel + game->player.move_speed;
		if (!found_wall(game, game->player.x_pixel, new_pos) && !found_door(game, game->player.x_pixel, new_pos))
			game->player.y_pixel = new_pos;
		else
		{
			slide_amount = game->player.move_speed * cosf(game->player.pva);
			new_pos = game->player.x_pixel + slide_amount;
			if (!found_wall(game, new_pos, game->player.y_pixel) && !found_door(game, new_pos, game->player.y_pixel))
				game->player.x_pixel = new_pos;
		}
	}
}
