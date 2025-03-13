/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:05:39 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/12/21 15:05:41 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*redlang_line(char *str, int fd, char *buffer)
{
	int	nmbre_byte;

	nmbre_byte = 1;
	while (nmbre_byte > 0 && !ft_strchr(str, '\n'))
	{
		nmbre_byte = read(fd, buffer, BUFFER_SIZE);
		if (nmbre_byte == -1)
			return (NULL);
		else if (nmbre_byte == 0)
		{
			if (ft_strlen(str) > 0)
				return str;
			else
				return NULL;
		}
		buffer[nmbre_byte] = '\0';
		str = ft_strjoin(str, buffer);
	}
	return str;
}

char	*correcte_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = gc_malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*rest_line(char *str, char *line)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rest = gc_malloc(ft_strlen(str) - ft_strlen(line) + 1);
	if (!rest)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		i++;
		while (str[i])
		{
			rest[j] = str[i];
			i++;
			j++;
		}
	}
	rest[j] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (str == NULL)
	{
		str = gc_malloc(1);
		str[0] = '\0';
		if (str == NULL)
			return (NULL);
	}
	buffer = gc_malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	str = redlang_line(str, fd, buffer);
	if (!str)
		return (NULL);
	line = correcte_line(str);
	str = rest_line(str, line);
	if (!str)
		return ( NULL);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
//     char *str;
//     int a = open("file.txt", O_RDONLY);
//     while (1)
//     {
//         str = get_next_line(a);
//         printf("line: \"%s\"\n", str);
//         free(str);
//         if (!str)
//             break ;
//     }
//     str = get_next_line(a);
//     printf("line: \"%s\"\n", str);
//     free(str);
//     return (0);
// }
