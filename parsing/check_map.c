/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:24:13 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/09 19:59:24 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void player_position(char *line, bool *player)
{
    int i;

    i = 0;

    while (line[i] && line[i] == ' ')
        i++;
    while (line[i] == '1' || line[i] == ' ' || line[i] == '0' || line[i] == 'C' || line[i] == 'O')
            i++;
    if (line[i] != '\0')
    {
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
        {
            if (*player == true)
                ft_panic("Map is not valid");
            *player = true;
        }
        else
            ft_panic("Map is not valid");
    }
    if (line[i++] == '\0')
        return ;
    while (line[i] == '1' || line[i] == ' ' || line[i] == '0')
        i++;
    if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
        ft_panic("Map is not valid444");
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
    i = 0;
    while (data->map[++i] != NULL)
        player_position(data->map[i], &player);
    j = -1;
    while (data->map[i - 1][++j] != '\0')
    {
        if (data->map[i-1][j] != '1' && data->map[i-1][j] != ' ')
            ft_panic("Map is not valid");
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
