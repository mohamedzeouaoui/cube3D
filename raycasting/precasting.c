/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:01:47 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/12 07:32:10 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_textures_img3(t_game *game)
{
	game->p2.img = mlx_xpm_file_to_image(game->window.cnx, game->p2.path, \
	&game->p2.width, &game->p2.height);
	if (!game->p2.img)
		ft_close(game, 1);
	game->p2.tex_data = mlx_get_data_addr(game->p2.img, &game->p2.bpp, \
	&game->p2.line_length, &game->p2.endian);
	game->p3.img = mlx_xpm_file_to_image(game->window.cnx, game->p3.path, \
	&game->p3.width, &game->p3.height);
	if (!game->p3.img)
		ft_close(game, 1);
	game->p3.tex_data = mlx_get_data_addr(game->p3.img, &game->p3.bpp, \
	&game->p3.line_length, &game->p3.endian);
}

void	init_textures_img2(t_game *game)
{
	game->door.img = mlx_xpm_file_to_image(game->window.cnx, game->door.path, \
	&game->door.width, &game->door.height);
	if (!game->door.img)
		ft_close(game, 1);
	game->door.tex_data = mlx_get_data_addr(game->door.img, &game->door.bpp, \
	&game->door.line_length, &game->door.endian);
	game->p0.img = mlx_xpm_file_to_image(game->window.cnx, game->p0.path, \
	&game->p0.width, &game->p0.height);
	if (!game->p0.img)
		ft_close(game, 1);
	game->p0.tex_data = mlx_get_data_addr(game->p0.img, &game->p0.bpp, \
	&game->p0.line_length, &game->p0.endian);
	game->p1.img = mlx_xpm_file_to_image(game->window.cnx, game->p1.path, \
	&game->p1.width, &game->p1.height);
	if (!game->p1.img)
		ft_close(game, 1);
	game->p1.tex_data = mlx_get_data_addr(game->p1.img, &game->p1.bpp, \
	&game->p1.line_length, &game->p1.endian);
	init_textures_img3(game);
}

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
	init_textures_img2(game);
	game->window.img.addr = mlx_get_data_addr(game->window.img.img, \
	&game->window.img.bpp, \
	&game->window.img.line_length, &game->window.img.endian);
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
	mlx_hook(game->window.win, 17, 0, ft_close, &game->window);
	mlx_loop_hook(game->window.cnx, drawer, game);
	mlx_hook(game->window.win, 17, 0, ft_close, game);
	mlx_hook(game->window.win, 6, 1L<<6, mouse_move_hook, game);
	mlx_hook(game->window.win, KeyPress, KeyPressMask, keys, game);
	mlx_key_hook(game->window.win, doors, game);
	mlx_mouse_hook(game->window.win, animation, game);
	mlx_loop(game->window.cnx);
}
