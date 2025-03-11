#include "../cub3d.h"

void destroy_images(t_game *game)
{
	if (game->wall_north.img)
		mlx_destroy_image(game->window.cnx, game->wall_north.img);
	if (game->wall_south.img)
		mlx_destroy_image(game->window.cnx, game->wall_south.img);
	if (game->wall_east.img)
		mlx_destroy_image(game->window.cnx, game->wall_east.img);
	if (game->wall_west.img)
		mlx_destroy_image(game->window.cnx, game->wall_west.img);
}

int ft_close(t_game *game)
{
	destroy_images(game);
	mlx_destroy_image(game->window.cnx, game->window.img.img);
	mlx_destroy_window(game->window.cnx, game->window.win);
	mlx_destroy_display(game->window.cnx);
	free(game->window.cnx);
	free_all_in_gc();
	exit(0);
}

int drawer(t_game *game)
{
	draw_map(game);
	return (0);
}

void mv_ea_we(t_game *game)
{
	if (facing_east(game)) // east ->
	{
		game->keys.left = 115;
		game->keys.right = 119;
		game->keys.forward = 97;
		game->keys.backward = 100;
		game->player.direction = 1;
	}
	else if (facing_west(game)) // west <-
	{
		game->keys.left = 119;
		game->keys.right = 115;
		game->keys.forward = 100;
		game->keys.backward = 97;
		game->player.direction = 3;
	}
}

void dynamic_control(t_game *game)
{
	if (facing_south(game)) // south
	{
		game->keys.left = 100;
		game->keys.right = 97;
		game->keys.forward = 115;
		game->keys.backward = 119;
		game->player.direction = 2;
	}
	else if (facing_north(game)) // north
	{
		game->keys.left = 97;
		game->keys.right = 100;
		game->keys.forward = 119;
		game->keys.backward = 115;
		game->player.direction = 0;
	}
	mv_ea_we(game);
}

void move_player(int keycode, t_game *game, int new_pos)
{
	float slide_amount = 0;
	if (keycode == game->keys.left)
	{
		new_pos = game->player.x_pixel - game->player.move_speed;
		if (!found_wall(game, new_pos - 5, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
	if (keycode == game->keys.right)
	{
		new_pos = game->player.x_pixel + game->player.move_speed;
		if (!found_wall(game, new_pos + 5, game->player.y_pixel))
			game->player.x_pixel = new_pos;
	}
	if (keycode == game->keys.forward)
	{
		new_pos = game->player.y_pixel - game->player.move_speed;
		if (!found_wall(game, game->player.x_pixel, new_pos - 5))
			game->player.y_pixel = new_pos;
	}
	if (keycode == game->keys.backward)
	{
		new_pos = game->player.y_pixel + game->player.move_speed;
		if (!found_wall(game, game->player.x_pixel, new_pos + 5))
			game->player.y_pixel = new_pos;
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
		ft_close(game);
	if (keycode == 65361)
		game->player.pva = normalize_angle(game->player.pva - (game->player.rotaion_speed));
	if (keycode == 65363)
		game->player.pva = normalize_angle(game->player.pva + (game->player.rotaion_speed));
	dynamic_control(game);
	move_player(keycode, game, new_pos);
}
