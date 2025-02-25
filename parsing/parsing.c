/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:26:14 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/23 17:26:16 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void init_data(t_data *data)
{
    data->floor = malloc(sizeof(t_texture_F));
    data->ceiling = malloc(sizeof(t_texture_C));

    if (!data->floor || !data->ceiling)
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
}


int check_texture(char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\n')
        return (0);    
    if (line[i] == 'N' && line[i + 1] == 'O' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
        return (1);
    if (line[i] == 'S' && line[i + 1] == 'O' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
        return (1);
    if (line[i] == 'W' && line[i + 1] == 'E' && (line[i + 2] == ' ' || line[i + 2] == '\t'))
        return (1);
    if (line[i] == 'E' && line[i + 1] == 'A'&& (line[i + 2] == ' ' || line[i + 2] == '\t'))
        return (1);
    if (line[i] == 'F'&& (line[i + 1] == ' ' || line[i + 1] == '\t'))
        return (1);
    if (line[i] == 'C'&& (line[i + 1] == ' ' || line[i + 1] == '\t'))
        return (1);
    else
    {
        free(line);
        print_error("Wrong texture");
    }
    return (0);
}

char *check_valid_texture(char *texture, char *line, int len)
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
    map_lines->line_NO = check_valid_texture("NO", map_lines->line_NO, 2);
    map_lines->line_SO = check_valid_texture("SO", map_lines->line_SO, 2);
    map_lines->line_WE = check_valid_texture("WE", map_lines->line_WE, 2);
    map_lines->line_EA = check_valid_texture("EA", map_lines->line_EA, 2);
    map_lines->line_F = check_valid_texture("F", map_lines->line_F, 1);
    map_lines->line_C = check_valid_texture("C", map_lines->line_C, 1);

}

void ft_get_texture(char *line, t_texture *map_lines)
{
    int i;

    i = 0;
    while (line[i] == ' ')
        i++;
    // printf("line = %s\n", line);
    // printf("i = %d\n", i);
    if (line[i] == 'N' && line[i + 1] == 'O')
        map_lines->line_NO = ft_strdup(line);
    else if (line[i] == 'S' && line[i + 1] == 'O')
        map_lines->line_SO = ft_strdup(line);
    else if (line[i] == 'W' && line[i + 1] == 'E')
        map_lines->line_WE = ft_strdup(line);
    else if (line[i] == 'E' && line[i + 1] == 'A')
        map_lines->line_EA = ft_strdup(line);
    else if (line[i] == 'F')
        map_lines->line_F = ft_strdup(line);
    else if (line[i] == 'C')
        map_lines->line_C = ft_strdup(line);
}


int		ft_check_file(char *file, t_data *data)
{
    char	*line;

    data->fd_map = open(file, O_RDONLY);
    if (data->fd_map == -1)
        print_error("File not found");
    
    while (1)
    {
        line = get_next_line(data->fd_map);
        
        if (line[0] == '\n')
        {
            free(line);
            continue;
        }  
        if (line == NULL || ft_isdigit(line[0]))
            break;
        // printf("line = %s\n", line);
        if (check_texture(line))
            ft_get_texture(line, data->map_lines);
        free(line);
    }
    free(line);
    close(data->fd_map);
    return (1);
}
int check_path(char *path)
{
    int len;

    len = ft_strlen(path);
    if (path[len - 1] != 'b' || path[len - 2] != 'u' || path[len - 3] != 'c' || path[len - 4] != '.')
        print_error("Wrong file extension");
    return (1);
}

void check_color(char *color)
{
    int i;

    i = 0;
    while (color[i])
    {
        if (color[i] == '+')
            i++;
        if (color[i] == ',' && color[i + 1] == '+')
            i += 2;    
        if ((!ft_isdigit(color[i]) && color[i] != ',') || (color[i] == ',' && color[i + 1] == ','))
            print_error("Wrong color format");
        i++;
    }
}

void check_color_F_C(t_texture *map_lines)
{
    // int i;
    // int j;

    // i = 0;
    // j = 0;
    
    check_color(map_lines->line_F);
    check_color(map_lines->line_C);
    // while (map_lines->line_C[j])
    // {
    //     if (map_lines->line_C[j] == '+')
    //         j++;
    //     if (map_lines->line_C[j] == ',' && map_lines->line_C[j + 1] == '+')
    //         j += 2;
    //     if ((!ft_isdigit(map_lines->line_C[j]) && map_lines->line_C[j] != ',') || (map_lines->line_C[j] == ',' && map_lines->line_C[i + 1] == ','))
    //         print_error("Wrong color format");
    //     j++;
    // }
}

int check_valide_color(int color)
{
    if (color < 0 || color > 255)
        print_error("Wrong color format");
    printf("color = %d\n", color);
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

int check_args(int argc, char **argv, t_data *data)
{
    if (argc != 2)
        print_error("Wrong number of arguments");
    check_path(argv[1]);
    init_data(data);
    ft_check_file(argv[1], data);
    store_texture(data->map_lines);
    check_color_F_C(data->map_lines);
    convert_F_C_to_RGB(data);
    // printf("NO = %s//\n", data->map_lines->line_NO);
    // printf("SO = %s//\n", data->map_lines->line_SO);
    // printf("WE = %s//\n", data->map_lines->line_WE);
    // printf("EA = %s\n", data->map_lines->line_EA);
    // printf("F = %s\n", data->map_lines->line_F);
    // printf("C = %s\n", data->map_lines->line_C);

    return (1);
}