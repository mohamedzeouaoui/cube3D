/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:51:39 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/09 02:51:42 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
            ft_panic("Wrong color");
        i++;
    }
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] != '\0' && line[i] != '\n')
        ft_panic("Wrong color");
    return ;
}

void check_valid_color_norm(char *line, int *i, int *j)
{
    while (line[*i] != '\0' && line[*i] != '\n' && line[*i] != ' ' && line[*i] != '\t')
    {
        if (line[*i]== '+' && line[(*i) - 1] == ',')
                (*i)++;
        if (ft_isdigit(line[*i]) == 0 && line[*i] != ',')
            ft_panic("Wrong color");            
        if (line[*i] == ',')
            (*j)++;
        (*i)++;
    }
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
        check_valid_color_norm(line, &i, &j);
    }
    else
        ft_panic("Wrong color");    
    if (j != 2)
        ft_panic("Wrong color");
    return ;
}

