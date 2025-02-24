/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:31:25 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/23 17:31:27 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

// # include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>

// typedef struct s_map
// {
    // char    **map;
    // int     rows;
    // int     cols;
// }   t_map;
// 
// typedef struct s_player
// {
    // float   x;
    // float   y;
    // float   angle;
// }   t_player;
// 

typedef struct s_texture
{
	char				*line_NO;
    char                *line_SO;
    char                *line_WE;
    char                *line_EA;
    char                *line_F;
    char                *line_C;
}						t_texture;


typedef struct s_data
{
    t_texture   *map_lines;
    int     fd_map;
}   t_data;

int ft_strlen(char *str);
int check_args(int argc, char **argv, t_data *data);
char	*get_next_line(int fd);
void print_error(char *str);
int ft_isdigit(char c);
char * ft_strdup(char *str);

# endif
