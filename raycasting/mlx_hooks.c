#include "../cub3d.h"

int ft_close(t_window *window)
{
	mlx_destroy_window(window->cnx, window->win);
	mlx_destroy_display(window->cnx);
	exit(0);
}

void draw_animation(t_game *game, t_tex *image)
{
	int y_start = HEIGHT - image->height;
	while(y_start < HEIGHT)
	{
		int x_start = WIDTH / 2 - image->width / 2;
		while(x_start < WIDTH / 2 + image->width / 2)
		{
			int color = *(unsigned int *)(image->tex_data + (4 * image->width * (y_start - (HEIGHT - image->height)) + 4 * (x_start - (WIDTH / 2 - image->width / 2))));
			if (color != 0xff000000) // Eliminate black pixels
				ft_mlx_pixel_put(game, x_start, y_start, color);
			x_start++;
		}
		y_start++;
	}
}

int drawer(t_game *game)
{
	draw_map(game);
	draw_mini_map(game);
	if (!game->animation)
		draw_animation(game, &game->p0);
	else if (game->animation == 1)
	{
		// for (int i = 0; i < 150; i++)
			draw_animation(game, &game->p1);
		// game->animation = 2;
	}
	else if (game->animation == 2)
	{
		// for (int i = 0; i < 200; i++)
			draw_animation(game, &game->p2);
		// game->animation = 3;
	}
	if (game->animation == 3)
	{
		// for (int i = 0; i < 150; i++)
			draw_animation(game, &game->p3);
		// game->animation = 0;
	}
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
        if (!found_wall(game, new_pos - 5, game->player.y_pixel) && !found_door(game, new_pos - 5, game->player.y_pixel))
            game->player.x_pixel = new_pos;
        else
        {
            // Calculate slide amount for wall sliding
            slide_amount = game->player.move_speed * sinf(game->player.pva);
            new_pos = game->player.y_pixel + slide_amount;
            if (!found_wall(game, game->player.x_pixel, new_pos + 5) && !found_door(game, game->player.x_pixel, new_pos + 5))
                game->player.y_pixel = new_pos;
        }
    }
    else if (keycode == game->keys.right)
    {
        new_pos = game->player.x_pixel + game->player.move_speed;
        if (!found_wall(game, new_pos + 5, game->player.y_pixel) && !found_door(game, new_pos + 5, game->player.y_pixel))
            game->player.x_pixel = new_pos;
        else
        {
            slide_amount = game->player.move_speed * sinf(game->player.pva);
            new_pos = game->player.y_pixel + slide_amount;
            if (!found_wall(game, game->player.x_pixel, new_pos + 5) && !found_door(game, game->player.x_pixel, new_pos + 5))
                game->player.y_pixel = new_pos;
        }
    }
    else if (keycode == game->keys.forward)
    {
        new_pos = game->player.y_pixel - game->player.move_speed;
        if (!found_wall(game, game->player.x_pixel, new_pos - 5) && !found_door(game, game->player.x_pixel, new_pos - 5))
            game->player.y_pixel = new_pos;
        else
        {
            slide_amount = game->player.move_speed * cosf(game->player.pva);
            new_pos = game->player.x_pixel + slide_amount;
            if (!found_wall(game, new_pos + 5, game->player.y_pixel) && !found_door(game, new_pos + 5, game->player.y_pixel))
                game->player.x_pixel = new_pos;
        }
    }
    else if (keycode == game->keys.backward)
    {
        new_pos = game->player.y_pixel + game->player.move_speed;
        if (!found_wall(game, game->player.x_pixel, new_pos + 5) && !found_door(game, game->player.x_pixel, new_pos + 5))
            game->player.y_pixel = new_pos;
        else
        {
            slide_amount = game->player.move_speed * cosf(game->player.pva);
            new_pos = game->player.x_pixel + slide_amount;
            if (!found_wall(game, new_pos + 5, game->player.y_pixel) && !found_door(game, new_pos + 5, game->player.y_pixel))
                game->player.x_pixel = new_pos;
        }
    }
}

int keys(int keycode, void *game1)
{
	int new_pos = 0;
	float slide_amount = 0;
	t_game *game = game1;
	game->menu.entred = 0;
	// if (keycode == 65362)
	// 	game->menu.index = (game->menu.index + 1) % 2;
	// else if (keycode == 65364)
	// 	game->menu.index = (game->menu.index + 1) % 2;
	// if (keycode == 65293)
	// 	game->menu.entred = 1;
	if (keycode == 113 || 65307 == keycode)
		ft_close(&game->window);
	if (keycode == 65361)
	{
		game->key_pressed = 1;
		game->player.pva = normalize_angle(game->player.pva - (game->player.rotaion_speed));
	}
	if (keycode == 65363)
	{
		game->key_pressed = 1;
		game->player.pva = normalize_angle(game->player.pva + (game->player.rotaion_speed));
	}
	dynamic_control(game);
	move_player(keycode, game, new_pos);
	return 0;
}
