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

typedef struct s_texture_F
{
    int    R;
    int     G;
    int     B;
}   t_texture_F;

typedef struct s_texture_C
{
    int    R;
    int     G;
    int     B;
}   t_texture_C;


typedef struct s_data
{
    t_texture_F     *floor;
    t_texture_C     *ceiling;
    t_texture   *map_lines;
    char       **map;
    int     fd_map;
}   t_data;


 // parsing
int check_args(int argc, char **argv, t_data *data);
int		ft_check_file(char *file, t_data *data);
void store_texture(t_texture *map_lines);
void check_color_F_C(t_texture *map_lines);
void convert_F_C_to_RGB(t_data *data);
char	*ft_substr_parsing(char *s, int start, int len);
void check_valid_map(char *file, t_data *data);
int is_empty_line(char *line);

// utils

char	*get_next_line(int fd);
int ft_strlen(char *str);
void print_error(char *str);
int ft_isdigit(char c);
char * ft_strdup(char *str);
char	**ft_split(char *s, char c);
int	ft_atoi(char *str);

# endif
