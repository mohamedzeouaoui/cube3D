#include "cub3d.h"

int facing_north(t_game *game)
{
	return (game->player.pva > (225 * (PI / 180)) && game->player.pva < (315 * (PI / 180)));
}

int facing_south(t_game *game)
{
	return (game->player.pva > (45 * (PI / 180)) && game->player.pva < (135 * (PI / 180)));
}

int facing_west(t_game *game)
{
	return (game->player.pva > (135 * (PI / 180)) && game->player.pva < (225 * (PI / 180)));
}

int facing_east(t_game *game)
{
	return (game->player.pva > (315 * (PI / 180)) || game->player.pva < (45 * (PI / 180)));
}
