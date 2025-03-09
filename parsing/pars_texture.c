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
            print_error("Wrong texture");        
    }
    else
        print_error("Wrong texture");
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
            print_error("Wrong color");
        i++;
    }
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '\0' && line[i] != '\n')
        print_error("Wrong color");
    
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
                print_error("Wrong color");            
            if (line[i] == ',')
                j++;
            i++;
        }
    }
    else
        print_error("Wrong color");    
    if (j != 2)
        print_error("Wrong color");
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
        print_error("Wrong texture");    
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
        print_error("Wrong texture");
}

// void check_num_of_lines(char *file, t_data *data)
// {
//     char *line = NULL;
//     int i;
//     int j;
    
//     i = 0;
//     j = 0;
//     data->fd_map = open(file, O_RDONLY);
//     if (data->fd_map == -1)
//         print_error("File not found");
//     while (1)
//     {
//         line = get_next_line(data->fd_map);
//         if (line == NULL)
//             break;
//         if (is_empty_line(line) == 1)
//         {
//             free(line);
//             continue;
//         }
//         i++;
//         while (line[j] == ' ' || line[j] == '\t')
//             j++;
//         if (ft_isdigit(line[j]))
//             break;        
//         if (i > 6)
//             print_error("wrong texture");        
//         free(line);
//     }
//     free(line);
//     close(data->fd_map);
// }

int		ft_check_file(char *file, t_data *data)
{
    char	*line;
    int i;
    int j;

    i = 1;
    data->fd_map = open(file, O_RDONLY);
    if (data->fd_map == -1)
        print_error("File not found");
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

// void check_duplicate_texture(char *file,t_data *data)
// {
//     char *line;
//     int i;

//     i = 0;
//     data->fd_map = open(file, O_RDONLY);
//     if (data->fd_map == -1)
//         print_error("File not found");
//     while (1)
//     {
//         line = get_next_line(data->fd_map);
        
//         if (line == NULL)
//             break;
//         if (is_empty_line(line) == 1)
//         {
//             free(line);
//             continue;
//         }
//         while (line[i] == ' ' || line[i] == '\t')
//             i++;
        
//         if(ft_isdigit(line[i]))
//             break;
//         free(line);
//     }
    
// }

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


