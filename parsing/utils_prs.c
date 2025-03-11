/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:53:27 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/10 06:34:42 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


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
                    ft_panic("Map is not valid");
                }
            }
            j++;
        }
        i++;
    }
    
}

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
