/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:49:15 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/11 23:09:37 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
    map_lines->line_D = v_texture("D", map_lines->line_D, 1);
    map_lines->line_F = v_texture("F", map_lines->line_F, 1);
    map_lines->line_C = v_texture("C", map_lines->line_C, 1);

}

void ft_gettexture_dup(char *line, char **XX, bool *XX_flag)
{
    *XX = ft_gc_strdup(line);
    *XX_flag = true;
}
void ft_get_texture(char *line, t_texture *map_lines, t_data *data)
{
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == 'N' && line[i + 1] == 'O' && data->dup_texture->NO == false)
        ft_gettexture_dup(line, &map_lines->line_NO, &data->dup_texture->NO);
    else if (line[i] == 'S' && line[i + 1] == 'O' && data->dup_texture->SO == false)
        ft_gettexture_dup(line, &map_lines->line_SO, &data->dup_texture->SO);
    else if (line[i] == 'W' && line[i + 1] == 'E' && data->dup_texture->WE == false)
        ft_gettexture_dup(line, &map_lines->line_WE, &data->dup_texture->WE);
    else if (line[i] == 'E' && line[i + 1] == 'A' && data->dup_texture->EA == false)
        ft_gettexture_dup(line, &map_lines->line_EA, &data->dup_texture->EA);
    else if (line[i] == 'D' && data->dup_texture->D == false)
        ft_gettexture_dup(line, &map_lines->line_D, &data->dup_texture->D);
    else if (line[i] == 'F' && data->dup_texture->F == false)
        ft_gettexture_dup(line, &map_lines->line_F, &data->dup_texture->F);
    else if (line[i] == 'C' && data->dup_texture->C == false)
        ft_gettexture_dup(line, &map_lines->line_C, &data->dup_texture->C);
    else
        ft_panic("Wrong texture");
}
