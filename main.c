/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:35:17 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 20:36:20 by aakhrif          ###   ########.fr       */
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

int	main(int ac, char **av)
{
	static t_data	data;
	static t_game	game;

	if (ac != 2)
		ft_panic("Wrong number of arguments");
	check_path(av[1]);
	init_data(&data);
	ft_check_file(av[1], &data);
	check_valid_map(av[1], &data);
	store_texture(data.map_lines);
	convert_F_C_to_RGB(&data);
	// --------------------------
	game.view_height = 2.5;
	game.map = data.map;
	game.map_width = ft_strlen(game.map[0]);
	game.map_len = map_len(game.map);
	game.c_color = r_g_b(data.ceiling->R, data.ceiling->G, data.ceiling->B);
	game.f_color = r_g_b(data.floor->R, data.floor->G, data.floor->B);
	find_player(&game);
	init_keys(&game);
	ft_mlx(&game, &data);
}
