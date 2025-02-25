/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:46:24 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/23 23:46:26 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

char * ft_strdup(char *str)
{
    char *new_str;
    int i;

    i = 0;
    new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));

    if (!new_str)
        print_error("Malloc failed");
    while (str[i])
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return (new_str);
}

