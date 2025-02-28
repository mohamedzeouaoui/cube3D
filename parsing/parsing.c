/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:26:14 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/23 17:26:16 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

void init_data(t_data *data)
{
    data->floor = malloc(sizeof(t_texture_F));
    data->ceiling = malloc(sizeof(t_texture_C));

    if (!data->floor || !data->ceiling)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Initialize values
    data->floor->R = 0;
    data->floor->G = 0;
    data->floor->B = 0;

    data->ceiling->R = 0;
    data->ceiling->G = 0;
    data->ceiling->B = 0;
}


int check_path(char *path)
{
    int len;

    len = ft_strlen(path);
    if (path[len - 1] != 'b' || path[len - 2] != 'u' || path[len - 3] != 'c' || path[len - 4] != '.')
        print_error("Wrong file extension");
    return (1);
}


int check_args(int argc, char **argv, t_data *data)
{
    if (argc != 2)
        print_error("Wrong number of arguments");
    check_path(argv[1]);
    init_data(data);
    ft_check_file(argv[1], data);
    store_texture(data->map_lines);
    check_color_F_C(data->map_lines);
    convert_F_C_to_RGB(data);
    check_valid_map(argv[1], data);

    return (1);
}
