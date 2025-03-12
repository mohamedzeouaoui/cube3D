/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:12:24 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/12 13:12:30 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int main()
// {
// 	int fd = open("file.txt", O_WRONLY | O_CREAT, 0777);
// 	if (fd == -1)
// 	{
// 		printf("file can't be opened");
// 		return (0);
// 	}
// 	ft_putchar_fd('m', fd);
// 	close(fd);
// 	return 0;
// }