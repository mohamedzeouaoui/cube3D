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

int		ft_check_file(char *file)
{
    int		fd;
    char	*line;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nFile not found\n");
        return (0);
    }
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    return (1);
}
int check_path(char *path)
{
    int len;

    len = ft_strlen(path);
    if (path[len - 1] != 'b' || path[len - 2] != 'u' || path[len - 3] != 'c' || path[len - 4] != '.')
    {
        printf("Error\nWrong file extension\n");
        return (0);
    }
    return (1);
}

int check_args(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error\nWrong number of arguments\n");
        return (0);
    }
    if (!check_path(argv[1]))
        return (0);
    ft_check_file(argv[1]);
    return (1);
}