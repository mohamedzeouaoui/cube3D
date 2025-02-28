/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:24:13 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/26 22:24:15 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

int is_empty_line(char *line)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\n')
        return (1);
    
    i++;
    return (0);
}

void check_valid_map(char *file, t_data *data)
{
    char *line = NULL;

    data->fd_map = open(file, O_RDONLY);
    if (data->fd_map == -1)
        print_error("File not found");
    int i = 0;
    line = get_next_line(data->fd_map);
    free(line);
    while (1)
    {
        line = get_next_line(data->fd_map);
        if (line == NULL)
            break;
        if(is_empty_line(line) == 1)
        {
            printf("line %d is empty %s\n", i, line);
            free(line);
            continue;
        }
        if (!ft_isdigit(line[0]) || line[0] == '\n')
        {
            free(line);
            continue;
        }

        i++;
        free(line);
    }
}
