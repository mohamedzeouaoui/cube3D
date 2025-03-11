/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:26:14 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/11 09:33:48 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_spase_tab(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

void init_data(t_data *data)
{
    data->floor = gc_malloc(sizeof(t_texture_F));
    data->ceiling = gc_malloc(sizeof(t_texture_C));
    data->map_lines = gc_malloc(sizeof(t_texture));
    data->dup_texture = gc_malloc(sizeof(t_dup_texture));
    if (!data->floor || !data->ceiling || !data->map_lines || !data->dup_texture)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    // Initialize values
    data->dup_texture->NO = false;
    data->dup_texture->SO = false;
    data->dup_texture->WE = false;
    data->dup_texture->EA = false;
    data->dup_texture->F = false;
    data->dup_texture->C = false;
    data->map_lines->line_NO = false;
    data->map_lines->line_SO = false;
    data->map_lines->line_WE = false;
    data->map_lines->line_EA = false;
    data->map_lines->line_F = false;
    data->map_lines->line_C = false;
}


int check_path(char *path)
{
    int len;

    len = ft_strlen(path);
    if (path[len - 1] != 'b' || path[len - 2] != 'u' || path[len - 3] != 'c' || path[len - 4] != '.')
        ft_panic("Wrong file extension");
    return (1);
}
