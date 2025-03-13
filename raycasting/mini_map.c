/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:02:46 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/13 09:02:48 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_square2(t_game *game, int x_start, int y_start, int color)
{
    int y ;
    int x ;
	
    y = y_start;

    while (y < y_start + 15)
    {
        x = x_start;
        while (x < x_start + 15)
        {
            ft_mlx_pixel_put(game, x, y, color);
            x++;
        }
        y++;
    }
}


void draw_arrow(t_game *game, int x, int y, int color)
{
	x += 6;
	y += 6;
    if (game->player.direction == 0) 
        draw_filled_triangle_north(x, y, game, color);
    else if (game->player.direction == 1) 
        draw_filled_triangle_east(x, y, game, color);
    else if (game->player.direction == 2) 
        draw_filled_triangle_south(x, y, game, color);
    else if (game->player.direction == 3)  
        draw_filled_triangle_west(x, y, game, color);
}

void draw_mini_map(t_game *game)
{
    int player_x;
    int player_y;
    int x_off, y_off;
    int mini_map_width = 10;
    int mini_map_height = 8;
    int k;
    int l;
    int y;
    int x;

    player_x = game->player.x_pixel / BLOCK_SIZE;
    player_y = game->player.y_pixel / BLOCK_SIZE;
    y_off = 0;
    k = 0;
    while (k < mini_map_height)
    {
        l = 0;
        while (l < mini_map_width)
        {
            draw_square2(game, l * 15, k * 15, 0x000000);
            l++;
        }
        k++;
    }
    y = player_y - mini_map_height / 2;
    while (y < player_y + mini_map_height / 2)
    {
        x_off = 0;
        x = player_x - mini_map_width / 2;
        while (x < player_x + mini_map_width / 2)
        {
            if (y >= 0 && y < game->map_len && x >= 0 && x < game->map_width)
            {
                if (game->map[y][x] == '1')
                    draw_square2(game, x_off, y_off, 0x1c2367); // Wall
                else if (game->map[y][x] == 'C')
                    draw_square2(game, x_off, y_off, 0xce0000); // door
                else if (game->map[y][x] == 'O')
                    draw_square2(game, x_off, y_off, 0x19e62c);
                else if (game->map[y][x] == '0' || ft_strchr("NSWE", game->map[y][x]))
                    draw_square2(game, x_off, y_off, game->f_color); // Floor
            }
            x_off += 15;
            x++;
        }
        y_off += 15;
        y++;
    }
    draw_arrow(game, (mini_map_width / 2) * 15, (mini_map_height / 2) * 15, 0x236413);
}
