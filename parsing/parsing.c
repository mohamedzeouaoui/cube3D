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
    data->map_lines = malloc(sizeof(t_texture));
    data->dup_texture = malloc(sizeof(t_dup_texture));

    if (!data->floor || !data->ceiling || !data->map_lines || !data->dup_texture)
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
    check_valid_map(argv[1], data);
    store_texture(data->map_lines);
    // check_color_F_C(data->map_lines);
    convert_F_C_to_RGB(data);
    // check_valid_map(argv[1], data);
    // printf("NO: %s\n", data->map_lines->line_NO);
    // printf("SO: %s\n", data->map_lines->line_SO);
    // printf("WE: %s\n", data->map_lines->line_WE);
    // printf("EA: %s\n", data->map_lines->line_EA);
    // printf("F: %s\n", data->map_lines->line_F);
    // printf("C: %s\n", data->map_lines->line_C);
    // printf("R_F: %d\n", data->floor->R);
    // printf("G_F: %d\n", data->floor->G);
    // printf("B_F: %d\n", data->floor->B);
    // printf("R_F: %d\n", data->ceiling->R);
    // printf("G_F: %d\n", data->ceiling->G);
    // printf("B_F: %d\n", data->ceiling->B);



    return (1);
}
