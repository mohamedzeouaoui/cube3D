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

char	*v_texture(char *texture, char *line, int len)
{
	int	i;

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

void	store_texture(t_texture *map_lines)
{
	map_lines->line_no = v_texture("NO", map_lines->line_no, 2);
	map_lines->line_so = v_texture("SO", map_lines->line_so, 2);
	map_lines->line_we = v_texture("WE", map_lines->line_we, 2);
	map_lines->line_ea = v_texture("EA", map_lines->line_ea, 2);
	map_lines->line_d = v_texture("D", map_lines->line_d, 1);
	map_lines->line_f = v_texture("F", map_lines->line_f, 1);
	map_lines->line_c = v_texture("C", map_lines->line_c, 1);
}

void	ft_gettexture_dup(char *line, char **XX, bool *XX_flag)
{
	*XX = ft_gc_strdup(line);
	*XX_flag = true;
}

void	ft_get_texture(char *line, t_texture *map_lines, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && data->dup_texture->no == false)
		ft_gettexture_dup(line, &map_lines->line_no, &data->dup_texture->no);
	else if (line[i] == 'S' && line[i + 1] == 'O'
		&& data->dup_texture->so == false)
		ft_gettexture_dup(line, &map_lines->line_so, &data->dup_texture->so);
	else if (line[i] == 'W' && line[i + 1] == 'E'
		&& data->dup_texture->we == false)
		ft_gettexture_dup(line, &map_lines->line_we, &data->dup_texture->we);
	else if (line[i] == 'E' && line[i + 1] == 'A'
		&& data->dup_texture->ea == false)
		ft_gettexture_dup(line, &map_lines->line_ea, &data->dup_texture->ea);
	else if (line[i] == 'D' && data->dup_texture->d == false)
		ft_gettexture_dup(line, &map_lines->line_d, &data->dup_texture->d);
	else if (line[i] == 'F' && data->dup_texture->f == false)
		ft_gettexture_dup(line, &map_lines->line_f, &data->dup_texture->f);
	else if (line[i] == 'C' && data->dup_texture->c == false)
		ft_gettexture_dup(line, &map_lines->line_c, &data->dup_texture->c);
	else
		ft_panic("Wrong texture");
}
