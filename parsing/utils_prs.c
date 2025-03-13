/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:53:27 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/03/10 06:34:42 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_wall_in_last(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j + 1] != '\0')
			j++;
		while (data->map[i][j] == ' ')
			j--;
		if (data->map[i][j] != '1')
			ft_panic("Map is not valid");
		i++;
	}
}

void	check_last_line(char *line, char *prev_line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			if (line[i + 1] == '0' || line[i - 1] == '0' || prev_line[i] == '0')
				ft_panic("Map is not valid");
		}
		i++;
	}
}

void	check_first_line(char *line, char *next_line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			if (line[i + 1] == '0' || line[i - 1] == '0' || next_line[i] == '0')
				ft_panic("Map is not valid");
		}
		i++;
	}
}

void	check_zero_and_space(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	while (data->map[i + 1] != NULL)
	{
		j = 1;
		while (data->map[i][j + 1] != '\0')
		{
			if (data->map[i][j] == ' ')
			{
				if (data->map[i][j - 1] == '0' || data->map[i][j + 1] == '0'
					|| data->map[i - 1][j] == '0' || data->map[i + 1][j] == '0')
				{
					ft_panic("Map is not valid");
				}
			}
			j++;
		}
		i++;
	}
	check_first_line(data->map[0], data->map[1]);
	check_last_line(data->map[i], data->map[i - 1]);
	check_wall_in_last(data);
}

void	count_lines(char *file, t_data *data)
{
	char	*line;
	int		i;

	i = 1;
	data->fd_map = open(file, O_RDONLY);
	if (data->fd_map == -1)
		ft_panic("File not found");
	while (1)
	{
		line = get_next_line(data->fd_map);
		if (line == NULL)
			break ;
		i++;
	}
	data->num_lines = i;
	close(data->fd_map);
}
