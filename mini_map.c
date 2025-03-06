#include "cub3d.h"

void draw_square2(t_game *game, int x_start, int y_start, int color, int f)
{
	if (f == 0)
	{
		for (int y = y_start; y < y_start + 20; y++)
		{
			for (int x = x_start; x < x_start + 20; x++)
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

void draw_arrow(t_game *game, int x, int y, int color, int size)
{
    // Set default size if not specified
    if (size <= 0)
        size = 6;

	x += 6;
	y += 6;
    // Common variables for all arrow types
    int i, j;
    int outline_color = 0x000000; // Black outline

    // Draw  arrow shapes based on direction
    if (game->player.direction == 0) // Upward arrow (▲)
    {
        // Draw filled triangle
        for (i = -size; i <= size; i++)
        {
            for (j = 0; j <= size; j++)
            {
                // Calculate the position relative to the triangle's shape
                if (j <= size - abs(i))
                {
                    ft_mlx_pixel_put(game, x + i, y - j, color);
                }
            }
        }

        // Draw outline
        for (i = -size; i <= size; i++)
        {
            // Bottom line
            if (i > -size && i < size)
                ft_mlx_pixel_put(game, x + i, y, outline_color);
            
            // Left diagonal
            j = abs(i + size);
            if (j <= size)
                ft_mlx_pixel_put(game, x - size + j, y - j, outline_color);
            
            // Right diagonal
            j = abs(i - size);
            if (j <= size)
                ft_mlx_pixel_put(game, x + size - j, y - j, outline_color);
        }
    }
    else if (game->player.direction == 1) // Rightward arrow (▶)
    {
        // Draw filled triangle
        for (i = 0; i <= size; i++)
        {
            for (j = -size; j <= size; j++)
            {
                if (i <= size - abs(j))
                {
                    ft_mlx_pixel_put(game, x + i, y + j, color);
                }
            }
        }

        // Draw outline
        for (j = -size; j <= size; j++)
        {
            // Left line
            if (j > -size && j < size)
                ft_mlx_pixel_put(game, x, y + j, outline_color);
            
            // Top diagonal
            i = abs(j + size);
            if (i <= size)
                ft_mlx_pixel_put(game, x + i, y - size + i, outline_color);
            
            // Bottom diagonal
            i = abs(j - size);
            if (i <= size)
                ft_mlx_pixel_put(game, x + i, y + size - i, outline_color);
        }
    }
    else if (game->player.direction == 2) // Downward arrow (▼)
    {
        // Draw filled triangle
        for (i = -size; i <= size; i++)
        {
            for (j = 0; j <= size; j++)
            {
                if (j <= size - abs(i))
                {
                    ft_mlx_pixel_put(game, x + i, y + j, color);
                }
            }
        }

        // Draw outline
        for (i = -size; i <= size; i++)
        {
            // Top line
            if (i > -size && i < size)
                ft_mlx_pixel_put(game, x + i, y, outline_color);
            
            // Left diagonal
            j = abs(i + size);
            if (j <= size)
                ft_mlx_pixel_put(game, x - size + j, y + j, outline_color);
            
            // Right diagonal
            j = abs(i - size);
            if (j <= size)
                ft_mlx_pixel_put(game, x + size - j, y + j, outline_color);
        }
    }
    else if (game->player.direction == 3) // Leftward arrow (◀)
    {
        // Draw filled triangle
        for (i = 0; i <= size; i++)
        {
            for (j = -size; j <= size; j++)
            {
                if (i <= size - abs(j))
                {
                    ft_mlx_pixel_put(game, x - i, y + j, color);
                }
            }
        }

        // Draw outline
        for (j = -size; j <= size; j++)
        {
            // Right line
            if (j > -size && j < size)
                ft_mlx_pixel_put(game, x, y + j, outline_color);
            
            // Top diagonal
            i = abs(j + size);
            if (i <= size)
                ft_mlx_pixel_put(game, x - i, y - size + i, outline_color);
            
            // Bottom diagonal
            i = abs(j - size);
            if (i <= size)
                ft_mlx_pixel_put(game, x - i, y + size - i, outline_color);
        }
    }
}

void draw_mini_map(t_game *game)
{
	int player_x = game->player.x_pixel / BLOCK_SIZE;
	int player_y = game->player.y_pixel / BLOCK_SIZE;
	int x_start, y_start, x_off, y_off;
	int mini_map_width = 10;
	int mini_map_height = 10; 

	y_off = 0;
	for(int k = 0; k < mini_map_height; k++)
	{
		for (int l = 0; l < mini_map_width; l++)
			draw_square2(game, l * 20, k * 20, 0x000000, 0);
	}
	for (int y = player_y - mini_map_height / 2; y < player_y + mini_map_height / 2; y++)
	{
		x_off = 0;
		for (int x = player_x - mini_map_width / 2; x < player_x + mini_map_width / 2; x++)
		{
			if (y >= 0 && y < game->map_len && x >= 0 && x < game->map_width)
			{
				if (game->map[y][x] == '1')
					draw_square2(game, x_off, y_off, 0x00FFFF, 0); // Wall
				else if (game->map[y][x] == 'C')
					draw_square2(game, x_off, y_off, 0xFFFFFF, 0); // door
				else if (game->map[y][x] == '0' || game->map[y][x] == 'S')
					draw_square2(game, x_off, y_off, 0x000000, 0); // Floor
			}
			x_off += 20;
		}
		y_off += 20;
	}
	draw_arrow(game, (mini_map_width / 2) * 20, (mini_map_height / 2) * 20, 0xFF0000, 0);
}
