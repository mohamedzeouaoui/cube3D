/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:48:32 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/11 23:08:32 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_valid_texture(char A, char B, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == A && line[i + 1] == B)
	{
		i += 2;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '.' && line[i + 1] == '/')
			return ;
		else
			ft_panic("Wrong texture");
	}
	else
		ft_panic("Wrong texture");
	return ;
}

int	check_texture(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && check_spase_tab(line[i + 2]))
		check_valid_texture('N', 'O', line);
	else if (line[i] == 'S' && line[i + 1] == 'O' && check_spase_tab(line[i
				+ 2]))
		check_valid_texture('S', 'O', line);
	else if (line[i] == 'W' && line[i + 1] == 'E' && check_spase_tab(line[i
				+ 2]))
		check_valid_texture('W', 'E', line);
	else if (line[i] == 'E' && line[i + 1] == 'A' && check_spase_tab(line[i
				+ 2]))
		check_valid_texture('E', 'A', line);
	else if (line[i] == 'D' && check_spase_tab(line[i + 1]))
		check_valid_texture('D', ' ', line);
	else if (line[i] == 'F' && check_spase_tab(line[i + 1]))
		check_valid_color('F', line);
	else if (line[i] == 'C' && check_spase_tab(line[i + 1]))
		check_valid_color('C', line);
	else
		ft_panic("Wrong texture");
	return (1);
}

void	ft_check_file_norm(char **line, t_data *data, int *i)
{
	if (check_texture(*line) == 1)
	{
		ft_get_texture(*line, data->map_lines, data);
		(*i)++;
	}
	free(*line);
}

int	ft_check_file(char *file, t_data *data)
{
	char	*line;
	int		i;
	int		j;

	i = 1;
	data->fd_map = open(file, O_RDONLY);
	if (data->fd_map == -1)
		ft_panic("File not found");
	while (1)
	{
		line = get_next_line(data->fd_map);
		if (line == NULL)
			break ;
		j = 0;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (is_empty_line(line) == 1 || (i > 7 && line[j] == '1'))
		{
			free(line);
			continue ;
		}
		ft_check_file_norm(&line, data, &i);
	}
	close(data->fd_map);
	return (1);
}
