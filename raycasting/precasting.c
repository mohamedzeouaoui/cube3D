/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:12:21 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 20:23:28 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_textures_img(t_game *game)
{
	game->wall_south.img = mlx_xpm_file_to_image(game->window.cnx, \
	game->wall_south.path, &game->wall_south.width, &game->wall_south.height);
	if (!game->wall_south.img)
		ft_close(game, 1);
	game->wall_south.tex_data = mlx_get_data_addr(game->wall_south.img, \
	&game->wall_south.bpp, &game->wall_south.line_length, \
	&game->wall_south.endian);
	game->wall_east.img = mlx_xpm_file_to_image(game->window.cnx, \
	game->wall_east.path, &game->wall_east.width, &game->wall_east.height);
	if (!game->wall_east.img)
		ft_close(game, 1);
	game->wall_east.tex_data = mlx_get_data_addr(game->wall_east.img, \
	&game->wall_east.bpp, &game->wall_east.line_length, \
	&game->wall_east.endian);
	game->wall_west.img = mlx_xpm_file_to_image(game->window.cnx, \
	game->wall_west.path, &game->wall_west.width, &game->wall_west.height);
	if (!game->wall_west.img)
		ft_close(game, 1);
	game->wall_west.tex_data = mlx_get_data_addr(game->wall_west.img, \
	&game->wall_west.bpp, &game->wall_west.line_length, \
	&game->wall_west.endian);
}

void	ft_mlx_init(t_game *game, t_data *data)
{
	game->wall_north.path = data->map_lines->line_no;
	game->wall_south.path = data->map_lines->line_so;
	game->wall_east.path = data->map_lines->line_ea;
	game->wall_west.path = data->map_lines->line_we;
	game->window.cnx = mlx_init();
	game->window.win = mlx_new_window(game->window.cnx, WIDTH, HEIGHT, "cub3D");
	game->window.img.img = mlx_new_image(game->window.cnx, WIDTH, HEIGHT);
	if (!game->window.img.img)
		ft_close(game, 1);
	game->wall_north.img = mlx_xpm_file_to_image(game->window.cnx, \
	game->wall_north.path, &game->wall_north.width, &game->wall_north.height);
	if (!game->wall_north.img)
		ft_close(game, 1);
	game->wall_north.tex_data = mlx_get_data_addr(game->wall_north.img, \
	&game->wall_north.bpp, &game->wall_north.line_length, \
	&game->wall_north.endian);
	init_textures_img(game);
	game->window.img.addr = mlx_get_data_addr(game->window.img.img, \
	&game->window.img.bpp, &game->window.img.line_length, \
	&game->window.img.endian);
}

void	ft_mlx(t_game *game, t_data *data)
{
	ft_mlx_init(game, data);
	mlx_hook(game->window.win, 17, 0, ft_close, game);
	mlx_loop_hook(game->window.cnx, drawer, game);
	mlx_hook(game->window.win, KeyPress, KeyPressMask, keys, game);
	mlx_loop(game->window.cnx);
}
