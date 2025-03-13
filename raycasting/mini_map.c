#include "../cub3d.h"

void draw_square2(t_game *game, int x_start, int y_start, int color, int f)
{
	if (f == 0)
	{
		for (int y = y_start; y < y_start + 15; y++)
		{
			for (int x = x_start; x < x_start + 15; x++)
			{
				ft_mlx_pixel_put(game, x, y, color);
			}
		}
	}
	else
	{
		for (int y = y_start; y < y_start + 8; y++)
		{
			for (int x = x_start; x < x_start + 8; x++)
			{
				ft_mlx_pixel_put(game, x + 5, y + 5, color);
			}
		}
	}
}

void draw_arrow(t_game *game, int x, int y, int color)
{
    // Set default size if not specified
    int size;
    
    size = 6;
	x += 6;
	y += 6;
    // Common variables for all arrow types
    int i, j;

    // Draw  arrow shapes based on direction
    if (game->player.direction == 0) // Upward arrow (▲)
    {
        // Draw filled triangle
        i = -size;
        while (i <= size)
        {
            j = 0;
            while (j <= size)
            {
                // Calculate the position relative to the triangle's shape
                if (j <= size - abs(i))
                {
                    ft_mlx_pixel_put(game, x + i, y - j, color);
                }
                j++;
            }
            i++;
        }
    }
    else if (game->player.direction == 1) // Rightward arrow (▶)
    {
        // Draw filled triangle
        i = 0;
        while (i <= size)
        {
            j = -size;
            while (j <= size)
            {
                if (i <= size - abs(j))
                {
                    ft_mlx_pixel_put(game, x + i, y + j, color);
                }
                j++;
            }
            i++;
        }
    }
    else if (game->player.direction == 2) // Downward arrow (▼)
    {
        // Draw filled triangle
        i = -size;
        while (i <= size)
        {
            j = 0;
            while (j <= size)
            {
                if (j <= size - abs(i))
                {
                    ft_mlx_pixel_put(game, x + i, y + j, color);
                }
                j++;
            }
            i++;
        }
    }
    else if (game->player.direction == 3) // Leftward arrow (◀)
    {
        // Draw filled triangle
        i = 0;
        while ( i <= size)
        {
            j = -size;
            while (j <= size)
            {
                if (i <= size - abs(j))
                {
                    ft_mlx_pixel_put(game, x - i, y + j, color);
                }
                j++;
            }
            i++;
        }
    }
}

void draw_mini_map(t_game *game)
{
	int player_x = game->player.x_pixel / BLOCK_SIZE;
	int player_y = game->player.y_pixel / BLOCK_SIZE;
	int x_off, y_off;
	int mini_map_width = 10;
	int mini_map_height = 8; 

	y_off = 0;
	for(int k = 0; k < mini_map_height; k++)
	{
		for (int l = 0; l < mini_map_width; l++)
			draw_square2(game, l * 15, k * 15, 0x000000, 0);
	}
	for (int y = player_y - mini_map_height / 2; y < player_y + mini_map_height / 2; y++)
	{
		x_off = 0;
		for (int x = player_x - mini_map_width / 2; x < player_x + mini_map_width / 2; x++)
		{
			if (y >= 0 && y < game->map_len && x >= 0 && x < game->map_width)
			{
				if (game->map[y][x] == '1')
					draw_square2(game, x_off, y_off, 0x1c2367, 0); // Wall
				else if (game->map[y][x] == 'C')
					draw_square2(game, x_off, y_off, 0xce0000, 0); // door
                else if (game->map[y][x] == 'O')
                    draw_square2(game, x_off, y_off, 0x19e62c, 0);
				else if (game->map[y][x] == '0' || ft_strchr("NSWE", game->map[y][x]))
					draw_square2(game, x_off, y_off, game->f_color, 0); // Floor
			}
			x_off += 15;
		}
		y_off += 15;
	}
	draw_arrow(game, (mini_map_width / 2) * 15, (mini_map_height / 2) * 15, 0x236413);
    
}
