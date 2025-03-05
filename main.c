#include "cub3d.h"

int is_empty_line(char *line)
{
    int	i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\n' || line[i] == '\0')
        return (1);
    i++;
    return (0);
}

void init(t_game *game, char **av)
{
	game->filename = av[1];
	game->view_height = 2.5;
	game->wall.path = ft_strdup("wall.xpm");
	game->menu.menu_img.path = ft_strdup("menu.xpm");
	game->door.path = ft_strdup("door.xpm");
	game->p0.path = ft_strdup("p0.xpm");
}

void init_data(t_data *data)
{
	data->floor = malloc(sizeof(t_texture_F));
    data->ceiling = malloc(sizeof(t_texture_C));
    data->map_lines = malloc(sizeof(t_texture));
    data->dup_texture = malloc(sizeof(t_dup_texture));

    if (!data->floor || !data->ceiling || !data->map_lines || !data->dup_texture)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    // Initialize values
    data->floor->R = 0;
    data->floor->G = 0;
    data->floor->B = 0;

    data->ceiling->R = 0;
    data->ceiling->G = 0;
    data->ceiling->B = 0;

    data->map_lines->line_NO = false;
    data->map_lines->line_SO = false;
    data->map_lines->line_WE = false;
    data->map_lines->line_EA = false;
    data->map_lines->line_F = false;
    data->map_lines->line_C = false;
}

int map_len(char **map)
{
	int i = 0;
	while(map[i])
		i++;
	return i;
}

int	main(int ac, char **av)
{
	static t_data	data;
	static t_game	game;

	init_data(&data);
	check_valid_map(av[1], &data);	
	init(&game, av);
	
	game.map = data.map;
	game.map_width = data.max_len;
	game.map_len = map_len(game.map);
	find_player(&game);
	ft_mlx(&game);
}
