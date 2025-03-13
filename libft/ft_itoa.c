/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:08:41 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/22 09:28:25 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	if_nega(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static size_t	count_n(long n)
{
	size_t	cont;
	long	m;

	cont = 1;
	m = if_nega(n);
	while (m > 9)
	{
		m = m / 10;
		cont++;
	}
	return (cont);
}

static char	*allocate(int nmb_d)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * (nmb_d + 1));
	if (!ptr)
		return (NULL);
	return (ptr);
}

static void	line25(int idx, char *str, long num)
{
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 9)
	{
		str[idx] = num % 10 + '0';
		num = num / 10;
		idx--;
	}
	str[idx] = num + '0';
}

char	*ft_itoa(int n)
{
	int		nmbr_dj;
	long	num;
	int		idx;
	char	*str;

	num = n;
	nmbr_dj = count_n(n);
	if (num < 0)
	{
		nmbr_dj++;
	}
	idx = nmbr_dj;
	str = allocate(nmbr_dj);
	if (!str)
		return (NULL);
	str[idx] = '\0';
	idx--;
	line25(idx, str, num);
	return (str);
}
