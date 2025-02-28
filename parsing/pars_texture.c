/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:48:32 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/26 17:48:35 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

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
    else
    {
        printf("looooooooooooooooooool  ");
        return ;
    }
}
void check_num_of_lines(char *file, t_data *data)
{
    char *line = NULL;
    int i;
    int j;
    
    i = 0;
    j = 0;
    data->fd_map = open(file, O_RDONLY);
    if (data->fd_map == -1)
        print_error("File not found");
    while (1)
    {
        line = get_next_line(data->fd_map);
        if (line == NULL)
            break;
        if (is_empty_line(line) == 1)
        {
            free(line);
            continue;
        }
        i++;
        while (line[j] == ' ' || line[j] == '\t')
            j++;
        if (ft_isdigit(line[j]))
            break;        
        if (i > 6)
            print_error("wrong texture");        
        free(line);
    }
    free(line);
    close(data->fd_map);
}

int		ft_check_file(char *file, t_data *data)
{
    char	*line;
    int i;

    i = 1;
    check_num_of_lines(file, data);
    data->fd_map = open(file, O_RDONLY);
    if (data->fd_map == -1)
        print_error("File not found");
    printf("LINE = %d\n", data->fd_map);
    line = get_next_line(data->fd_map);
    free(line);

    while (1)
    {
        line = get_next_line(data->fd_map);
        printf("LINE = %s\n", line);
        if (line[0] == '\n')
        {
            free(line);
            continue;
        }  
        if (line == NULL || ft_isdigit(line[0]) || i == 5)
            break;
        i++;
        if (check_texture(line))
            ft_get_texture(line, data->map_lines);
        free(line);
    }
    free(line);
    close(data->fd_map);
    return (1);
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


