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

void check_valid_texture(char A, char B, char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == A && line[i + 1] == B)
    {
        i += 2;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '.' && line[i + 1] == '/')
            return ;
        else
            ft_panic("Wrong texture");        
    }
    else
        ft_panic("Wrong texture");
    return ;
}

void format_color(char *line)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (ft_isdigit(line[i]) || line[i] == ',' || (line[i] == '+' && ft_isdigit(line[i + 1]) && line[i - 1] != ','))
    {
        if (line[i] == ',')
        {
            j++;
            i++;
        }
        if (line[i] == '+')
            i++;
        if (ft_isdigit(line[i]) == 0)
            ft_panic("Wrong color");
        i++;
    }
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '\0' && line[i] != '\n')
        ft_panic("Wrong color");
    
    return ;
}

void check_valid_color(char A, char *line)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i++] == A)
    {
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i]== '+' && ft_isdigit(line[i + 1]))
            i++;        
        format_color(line+i);
        while (line[i] != '\0' && line[i] != '\n' && line[i] != ' ' && line[i] != '\t')
        {
            if (line[i]== '+' && line[i - 1] == ',')
                i++;
        if (ft_isdigit(line[i]) == 0 && line[i] != ',')
                ft_panic("Wrong color");            
            if (line[i] == ',')
                j++;
            i++;
        }
    }
    else
        ft_panic("Wrong color");    
    if (j != 2)
        ft_panic("Wrong color");
    return ;
}

int check_spase_tab(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}


int check_texture(char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == 'N' && line[i + 1] == 'O' && check_spase_tab(line[i + 2]))
        check_valid_texture('N', 'O', line);
    else if (line[i] == 'S' && line[i + 1] == 'O'&& check_spase_tab(line[i + 2]))
        check_valid_texture('S', 'O', line);
    else if (line[i] == 'W' && line[i + 1] == 'E'&& check_spase_tab(line[i + 2]))
        check_valid_texture('W', 'E', line);
    else if (line[i] == 'E' && line[i + 1] == 'A'&& check_spase_tab(line[i + 2]))
        check_valid_texture('E', 'A', line);
    else if (line[i] == 'F' && check_spase_tab(line[i + 1]))
        check_valid_color('F', line);
    else if (line[i] == 'C' && check_spase_tab(line[i + 1]))
        check_valid_color('C', line);
    else
        ft_panic("Wrong texture");    
    return (1);
}

void ft_get_texture(char *line, t_texture *map_lines, t_data *data)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == 'N' && line[i + 1] == 'O' && data->dup_texture->NO == false)
    {
        map_lines->line_NO = ft_strdup(line);
        data->dup_texture->NO = true;
    }
    else if (line[i] == 'S' && line[i + 1] == 'O' && data->dup_texture->SO == false)
    {
        map_lines->line_SO = ft_strdup(line);
        data->dup_texture->SO = true;
    }
    else if (line[i] == 'W' && line[i + 1] == 'E' && data->dup_texture->WE == false)
    {
        map_lines->line_WE = ft_strdup(line);
        data->dup_texture->WE = true;
    }
    else if (line[i] == 'E' && line[i + 1] == 'A' && data->dup_texture->EA == false)
    {
        map_lines->line_EA = ft_strdup(line);
        data->dup_texture->EA = true;
    }
    else if (line[i] == 'F' && data->dup_texture->F == false)
    {
        map_lines->line_F = ft_strdup(line);
        data->dup_texture->F = true;
    }
    else if (line[i] == 'C' && data->dup_texture->C == false)
    {
        map_lines->line_C = ft_strdup(line);
        data->dup_texture->C = true;
    }
    else
        ft_panic("Wrong texture");
}

int		ft_check_file(char *file, t_data *data)
{
    char	*line;
    int i;
    int j;

    i = 1;
    data->fd_map = open(file, O_RDONLY);
    if (data->fd_map == -1)
        ft_panic("File not found");
    while (1)
    {
        line = get_next_line(data->fd_map);
        if (line == NULL)
            break;
        j = 0;
        while (line[j] == ' ' || line[j] == '\t')
            j++;
        if (is_empty_line(line) == 1 || (i > 6 && line[j] == '1'))
        {
            free(line);
            continue;
        }
        if (check_texture(line) == 1)
        {
            ft_get_texture(line, data->map_lines, data);
            i++;
        }
        free(line);
    }
    close(data->fd_map);
    return (1);
}

int check_path(char *path)
{
    int len;

    len = ft_strlen(path);
    if (path[len - 1] != 'b' || path[len - 2] != 'u' || path[len - 3] != 'c' || path[len - 4] != '.')
        ft_panic("Wrong file extension");
    return (1);
}

char *v_texture(char *texture, char *line, int len)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (len == 2)
    {    
        if (line[i] == texture[0] && line[i + 1] == texture[1])
        {
            i += 3;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
        }
    }
    if (len == 1)
    {
        if (line[i] == texture[0])
        {
            i += 2;
            while (line[i] == ' ' || line[i] == '\t')
                i++;
        }
    }
    line = ft_substr_parsing(line, i, ft_strlen(line));
    return (line);
}

void store_texture(t_texture *map_lines)
{
    map_lines->line_NO = v_texture("NO", map_lines->line_NO, 2);
    map_lines->line_SO = v_texture("SO", map_lines->line_SO, 2);
    map_lines->line_WE = v_texture("WE", map_lines->line_WE, 2);
    map_lines->line_EA = v_texture("EA", map_lines->line_EA, 2);
    map_lines->line_F = v_texture("F", map_lines->line_F, 1);
    map_lines->line_C = v_texture("C", map_lines->line_C, 1);

}

int check_valide_color(int color)
{
    if (color < 0 || color > 255)
        ft_panic("Wrong color format");
    return (color);
}


void convert_F_C_to_RGB(t_data *data)
{
    char **str_F;
    char **str_C;

    str_C = ft_split(data->map_lines->line_C, ',');
    str_F = ft_split(data->map_lines->line_F, ',');
    data->floor->R = check_valide_color(ft_atoi(str_F[0]));
    data->floor->G = check_valide_color(ft_atoi(str_F[1]));
    data->floor->B = check_valide_color(ft_atoi(str_F[2]));
    data->ceiling->R = check_valide_color(ft_atoi(str_C[0]));
    data->ceiling->G = check_valide_color(ft_atoi(str_C[1]));
    data->ceiling->B = check_valide_color(ft_atoi(str_C[2]));
    free(str_C);
    free(str_F);
}

void init_keys(t_game *game)
{
    if (game->map[game->player.y][game->player.x] == 'N')
    {
        game->keys.left = 97;
		game->keys.right = 100;
		game->keys.forward = 119;
		game->keys.backward = 115;
		game->player.direction = 0;
    }
    if (game->map[game->player.y][game->player.x] == 'W')
    {
        game->keys.left = 119;
		game->keys.right = 115;
		game->keys.forward = 100;
		game->keys.backward = 97;
		game->player.direction = 3;
    }
    if (game->map[game->player.y][game->player.x] == 'E')
    {
        game->keys.left = 115;
		game->keys.right = 119;
		game->keys.forward = 97;
		game->keys.backward = 100;
		game->player.direction = 1;
    }
    if (game->map[game->player.y][game->player.x] == 'S')
    {
        game->keys.left = 100;
		game->keys.right = 97;
		game->keys.forward = 115;
		game->keys.backward = 119;
		game->player.direction = 2;
    }
}

int	main(int ac, char **av)
{
	static t_data	data;
	static t_game	game;

    if (ac != 2)
        ft_panic("Wrong number of arguments");
    check_path(av[1]);
	init_data(&data);
    ft_check_file(av[1], &data);
	check_valid_map(av[1], &data);	
    store_texture(data.map_lines);
    convert_F_C_to_RGB(&data);
// --------------------------------------------------------------------------------------------
    game.view_height = 2.5;
	game.map = data.map;
	game.map_width = data.max_len;
	game.map_len = map_len(game.map);
	find_player(&game);
    init_keys(&game);
	ft_mlx(&game, &data);
}
