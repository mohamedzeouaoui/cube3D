#include "../cub3d.h"

int mouse_move_hook(int x, int y, void *game1)
{
	t_game *game = (t_game *)game1;
	game->key_pressed = 1;
	static int last_x = -1;

	if (last_x == -1)
		last_x = x;
	if (x > last_x)
		game->player.pva = normalize_angle(game->player.pva + (game->player.rotaion_speed));
	else if (x < last_x)
		game->player.pva = normalize_angle(game->player.pva - (game->player.rotaion_speed));
	last_x = x;
	if (game->player.pva > (45 * (PI / 180)) && game->player.pva < (135 * (PI / 180)))
	{
		game->keys.left = 100;
		game->keys.right = 97;
		game->keys.forward = 115;
		game->keys.backward = 119;
		game->player.direction = 2;
	}
	else if (game->player.pva > (225 * (PI / 180)) && game->player.pva < (315 * (PI / 180)))
	{
		game->keys.left = 97;
		game->keys.right = 100;
		game->keys.forward = 119;
		game->keys.backward = 115;
		game->player.direction = 0;
	}
	else if (game->player.pva > (315 * (PI / 180)) || game->player.pva < (45 * (PI / 180)))
	{
		game->keys.left = 115;
		game->keys.right = 119;
		game->keys.forward = 97;
		game->keys.backward = 100;
		game->player.direction = 1;
	}
	else if (game->player.pva > (135 * (PI / 180)) && game->player.pva < (225 * (PI / 180)))
	{
		game->keys.left = 119;
		game->keys.right = 115;
		game->keys.forward = 100;
		game->keys.backward = 97;
		game->player.direction = 3;
	}
	return (0);
}
