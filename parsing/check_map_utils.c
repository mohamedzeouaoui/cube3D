/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:56:02 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/11 22:59:36 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\n' || line[i] == '\0')
        return (1);
    
    i++;
    return (0);
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


void stor_map_norm(int *j, int *i, int *l, t_data *data)
{
    if (*l < data->max_len - 1)
    {
        while (*l < data->max_len - 2)
        {
            data->map[*j][*l] = ' ';
            (*l)++;
        }
    }
    data->map[*j][*l] = '\0';
    (*j)++;
    (*i)++;
}


void stor_map(t_data *data, int i)
{
    int j;
    int k;
    int l;

    j = 0;
    data->map = gc_malloc(sizeof(char *) * data->num_lines + 1);
    if (!data->map)
        ft_panic("malloc failed");
    while (data->file[i] != NULL)
    {
        data->map[j] = gc_malloc(sizeof(char) * (data->max_len + 1));
        if (!data->map[j])
            ft_panic("malloc failed");
        k = 0;
        l = 0;
        while (data->file[i][k] != '\0' && data->file[i][k] != '\n' && l < data->max_len)
        {
            data->map[j][l] = data->file[i][k];
            k++;
            l++;
        }
        stor_map_norm(&j, &i, &l, data);
    }
    data->map[j] = NULL;
}
