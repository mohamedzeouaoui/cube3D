/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:24:13 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/05 17:14:16 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void count_lines(char * file, t_data *data)
{
    char *line;
    int i;

    i = 1;
    data->fd_map = open(file, O_RDONLY);
    if (data->fd_map == -1)
        ft_panic("File not found");
    while (1)
    {
        line = get_next_line(data->fd_map);
        if (line == NULL)
            break;
        i++;
        free(line);
    }
    data->num_lines = i;
    close(data->fd_map);

}

void stor_file(char *file,t_data *data)
{
    char *line;
    int i;

    i = 0;
    count_lines(file, data);
    data->fd_map = open(file, O_RDONLY);
    if (data->fd_map == -1)
        ft_panic("File not found");
    data->file = malloc(sizeof(char *) * data->num_lines + 1);
    if (!data->file)
        ft_panic("Malloc failed");
    while (1)
    {
        line = get_next_line(data->fd_map);
        if (line == NULL)
            break;
        data->file[i] = ft_strdup(line);
        i++;
        free(line);
    }
    data->file[i] = NULL;
    close(data->fd_map);
}
void stor_map(t_data *data, int i)
{
    int j;
    int k;
    int l;

    j = 0;

    data->map = malloc(sizeof(char *) * data->num_lines + 1);
    if (!data->map)
        ft_panic("Malloc failed");
    while (data->file[i] != NULL)
    {
        data->map[j] = malloc(sizeof(char) * data->max_len);
        if (!data->map[j])
            ft_panic("Malloc failed");
        k = 0;
        l = 0;
        while (data->file[i][k] != '\0' && data->file[i][k] != '\n' && l < data->max_len)
        {
            data->map[j][l] = data->file[i][k];
            k++;
            l++;
        }
        if (l < data->max_len - 1)
        {
            while (l < data->max_len)
            {
                data->map[j][l] = ' ';
                l++;
            }
        }
        data->map[j][l] = '\0';
        j++;
        i++;
    }
    data->map[j] = NULL;
}

void max_len_of_map(t_data *data, int i)
{
    int k;
    int max;

    k = 0;
    max = 0;
    while (data->file[i] != NULL)
    {
        k = 0;
        while (data->file[i][k] != '\0' && data->file[i][k] != '\n')
            k++;
        if (k > max)
            max = k;
        i++;
    }
    data->max_len = max;
}

void check_line_of_map(t_data *data)
{
    int i;
    bool is_empty;

    i = 0;
    is_empty = false;
    while (data->map[i] != NULL)
    {
        while (data->map[i] && is_empty_line(data->map[i]) == 1) 
        {
            is_empty = true;
            i++;
        }
        if (data->map[i] == NULL )
            break;
        else if(is_empty == true)
            ft_panic("Map is not valid");
        i++;
    }
    i = 0;
    while (data->map[i] && is_empty_line(data->map[i]) == 0)
        i++;
    data->map[i] = NULL;
}

void check_zero_and_space(t_data *data)
{
    int i;
    int j;

    i = 1;
    while (data->map[i + 1] != NULL)
    {
        j = 1;
        while (data->map[i][j + 1] != '\0')
        {
            if (data->map[i][j] == ' ')
            {
                if (data->map[i][j - 1] == '0' || data->map[i][j + 1] == '0' || data->map[i - 1][j] == '0' || data->map[i + 1][j] == '0')
                {
                    printf(">%s<\n", data->map[i]);
                    ft_panic("Map is not valid");
                }
                
            }
            j++;
        }
        i++;
    }
    
}

void cheack_wall(t_data *data)
{
    int i;
    int j;
    bool player;

    i = 0;
    player = false;
    j = 0;
    while (data->map[i][j] != '\0')
    {
        if (data->map[i][j] != '1' && data->map[i][j] != ' ')
            ft_panic("Map is not valid");
        j++;
    }
    i = 1;
    while (data->map[i] != NULL)
    {
        j = 0;
        while (data->map[i][j] == ' ')
            j++;
        while (data->map[i][j] == '1' || data->map[i][j] == ' ' || data->map[i][j] == '0')
            j++;
        if (data->map[i][j] != '\0')
            {
                if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'W' || data->map[0][j] == 'E')
                {
                    if (player == true)
                        ft_panic("Map is not valid");
                    player = true;
                }
                else
                    ft_panic("Map is not valid");
            }
        i++;
    }
    j = 0;
    while (data->map[i - 1][j] != '\0')
    {
        if (data->map[i-1][j] != '1' && data->map[i-1][j] != ' ')
        {
            ft_panic("Map is not valid");
        }
        j++;
    }
    if (player == false)
        ft_panic("Map is not valid");
    check_zero_and_space(data);
}

void check_valid_map(char *file, t_data *data)
{
    int i;
    int j;

    i = 0;
    stor_file(file, data);
    while (1)
    {
        j = 0;
        while (data->file[i][j] == ' ' || data->file[i][j] == '\t')
            j++;
        if(data->file[i][j] == '1')
        {
            max_len_of_map(data, i);
            stor_map(data, i);
            break;
        }
        i++;
    }
    check_line_of_map(data);
    cheack_wall(data);
}
