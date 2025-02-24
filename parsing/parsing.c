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

int check_texture(char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ')
        i++;
    if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
        return (1);
    if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
        return (1);
    if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
        return (1);
    if (line[i] == 'E' && line[i + 1] == 'A'&& line[i + 2] == ' ')
        return (1);
    if (line[i] == 'F'&& line[i + 1] == ' ')
        return (1);
    if (line[i] == 'C'&& line[i + 1] == ' ')
        return (1);
    else
    {
        free(line);
        print_error("Wrong texture");
    }
    return (0);
}
void ft_get_texture(char *line, t_texture *map_lines)
{
    int i;

    i = 0;
    while (line[i] == ' ')
        i++;
    printf("line = %s\n", line);
    printf("i = %d\n", i);
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

int check_args(int argc, char **argv, t_data *data)
{
    if (argc != 2)
        print_error("Wrong number of arguments");
    check_path(argv[1]);
    ft_check_file(argv[1], data);
    return (1);
}