/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:55:24 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/26 17:55:26 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_color(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (color[i] == '+')
			i++;
		if (color[i] == ',' && color[i + 1] == '+')
			i += 2;
		if ((!ft_isdigit(color[i]) && color[i] != ',') || (color[i] == ','
				&& color[i + 1] == ','))
			ft_panic("Wrong color format");
		i++;
	}
}

void	check_color_fc(t_texture *map_lines)
{
	check_color(map_lines->line_f);
	check_color(map_lines->line_c);
}

int	check_valide_color(int color)
{
	if (color < 0 || color > 255)
		ft_panic("Wrong color format");
	return (color);
}

void	convert_fc_to_rgb(t_data *data)
{
	char	**str_f;
	char	**str_c;

	str_c = ft_split(data->map_lines->line_c, ',');
	str_f = ft_split(data->map_lines->line_f, ',');
	data->floor->r = check_valide_color(ft_atoi(str_f[0]));
	data->floor->g = check_valide_color(ft_atoi(str_f[1]));
	data->floor->b = check_valide_color(ft_atoi(str_f[2]));
	data->ceiling->r = check_valide_color(ft_atoi(str_c[0]));
	data->ceiling->g = check_valide_color(ft_atoi(str_c[1]));
	data->ceiling->b = check_valide_color(ft_atoi(str_c[2]));
	free(str_c);
	free(str_f);
}
