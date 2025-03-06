#include "cub3d.h"

int found_wall(t_game *game, int x_pos, int y_pos)
{
    if (x_pos < 0 || x_pos >= (game->map_width * BLOCK_SIZE) || y_pos < 0 || y_pos >= (game->map_len * BLOCK_SIZE))
        return (1);

    int x_map = x_pos / BLOCK_SIZE;
    int y_map = y_pos / BLOCK_SIZE;

    if (y_map >= game->map_len || x_map >= game->map_width)
        return (1);
    return (game->map[y_map][x_map] == '1');
}

int found_door(t_game *game, int x_pos, int y_pos)
{
    if (x_pos < 0 || x_pos >= (game->map_width * BLOCK_SIZE) || y_pos < 0 || y_pos >= (game->map_len * BLOCK_SIZE))
        return (1);
    int x_map = x_pos / BLOCK_SIZE;
    int y_map = y_pos / BLOCK_SIZE;

    return (game->map[y_map][x_map] == 'C');
}

double count_distance(double x1, double x2, double y1, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
