/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:55:24 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/26 17:55:26 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"


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
    check_color(map_lines->line_F);
    check_color(map_lines->line_C);
}

int check_valide_color(int color)
{
    if (color < 0 || color > 255)
        print_error("Wrong color format");
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
