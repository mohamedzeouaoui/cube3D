/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:14:24 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/12 13:14:31 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	mb;

	mb = -2147483648;
	if (n == mb)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		n = n * -1;
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(n, fd);
	}
	else if (n >= 0 && n <= 9)
	{
		ft_putchar_fd((n + 48), fd);
		return ;
	}
	else if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd((48 + n % 10), fd);
	}
}
