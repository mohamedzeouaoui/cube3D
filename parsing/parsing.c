/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:26:14 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/10 06:33:44 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_spase_tab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	init_data(t_data *data)
{
	data->floor = gc_malloc(sizeof(t_texture_F));
	data->ceiling = gc_malloc(sizeof(t_texture_C));
	data->map_lines = gc_malloc(sizeof(t_texture));
	data->dup_texture = gc_malloc(sizeof(t_dup_texture));
	if (!data->floor || !data->ceiling || !data->map_lines
		|| !data->dup_texture)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	data->dup_texture->no = false;
	data->dup_texture->so = false;
	data->dup_texture->we = false;
	data->dup_texture->ea = false;
	data->dup_texture->d = false;
	data->dup_texture->f = false;
	data->dup_texture->c = false;
	data->map_lines->line_no = false;
	data->map_lines->line_so = false;
	data->map_lines->line_we = false;
	data->map_lines->line_ea = false;
	data->map_lines->line_d = false;
	data->map_lines->line_f = false;
	data->map_lines->line_c = false;
}

int	check_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (path[len - 1] != 'b' || path[len - 2] != 'u' || path[len - 3] != 'c'
		|| path[len - 4] != '.')
		ft_panic("Wrong file extension");
	return (1);
}
