#include "cub3d.h"

void init(t_game *game, char **av)
{
	game->map = parse_map(av[1], game);
	game->map_width = ft_strlen(game->map[0]);
	game->filename = av[1];
	game->wall.path = ft_strdup("wall.xpm");
	game->view_height = 2.5;
	game->menu.menu_img.path = ft_strdup("menu.xpm");
	game->door.path = ft_strdup("door.xpm");
	game->p0.path = ft_strdup("p0.xpm");
	find_player(game);
}

int	main(int ac, char **av)
{
	static t_game	game;

    if (ac != 2)
		exit(ft_error(CUB3D_USAGE));
    if (ft_strcmp(".cub", av[1] + ft_strlen(av[1]) - 4) != 0)
		exit(ft_error(ERR_INVALID_FILENAME));
	init(&game, av);
	ft_mlx(&game);
}
