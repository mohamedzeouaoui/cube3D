/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:09:34 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/13 10:09:36 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	init_keys2(t_game *game)
{
	if (game->map[game->player.y][game->player.x] == 'E')
	{
		game->keys.left = 115;
		game->keys.right = 119;
		game->keys.forward = 97;
		game->keys.backward = 100;
		game->player.direction = 1;
	}
	if (game->map[game->player.y][game->player.x] == 'S')
	{
		game->keys.left = 100;
		game->keys.right = 97;
		game->keys.forward = 115;
		game->keys.backward = 119;
		game->player.direction = 2;
	}
}

void	init_keys(t_game *game)
{
	if (game->map[game->player.y][game->player.x] == 'N')
	{
		game->keys.left = 97;
		game->keys.right = 100;
		game->keys.forward = 119;
		game->keys.backward = 115;
		game->player.direction = 0;
	}
	if (game->map[game->player.y][game->player.x] == 'W')
	{
		game->keys.left = 119;
		game->keys.right = 115;
		game->keys.forward = 100;
		game->keys.backward = 97;
		game->player.direction = 3;
	}
	init_keys2(game);
}

void	*draw_animation_thread(void *game)
{
	t_game	*g;

	g = (t_game *)game;
	while (1)
	{
		if (g->exit_thread == 1)
			return (NULL);
		if (g->animation == 1)
		{
			usleep(100000);
			g->animation = 2;
		}
		else if (g->animation == 2)
		{
			usleep(100000);
			g->animation = 3;
		}
		else if (g->animation == 3)
		{
			usleep(100000);
			g->animation = 0;
		}
		else
		{
			usleep(100000);
		}
	}
}

int	main(int ac, char **av)
{
	static t_data	data;
	static t_game	game;

	game.window.cnx = mlx_init();
	game.window.win = mlx_new_window(game.window.cnx, WIDTH, HEIGHT, "Cub3D");
	if (ac != 2)
		ft_panic("Wrong number of arguments");
	check_path(av[1]);
	init_data(&data);
	ft_check_file(av[1], &data);
	check_valid_map(av[1], &data);
	store_texture(data.map_lines);
	convert_f_c_to_rgb(&data);
	// --------------------------------------------------------------------------------------------
	game.exit_thread = 0;
	game.view_height = 2.5;
	game.map = data.map;
	game.map_width = ft_strlen(game.map[0]);
	game.map_len = map_len(game.map);
	game.c_color = r_g_b(data.ceiling->r, data.ceiling->g, data.ceiling->b);
	game.f_color = r_g_b(data.floor->r, data.floor->g, data.floor->b);
	game.door.path = data.map_lines->line_d;
	game.p0.path = ft_gc_strdup("p0.xpm");
	game.p1.path = ft_gc_strdup("p1.xpm");
	game.p2.path = ft_gc_strdup("p2.xpm");
	game.p3.path = ft_gc_strdup("p3.xpm");
	find_player(&game);
	init_keys(&game);
	pthread_create(&game.thread, NULL, draw_animation_thread, &game);
	ft_mlx(&game, &data);
	free_all_in_gc();
}
