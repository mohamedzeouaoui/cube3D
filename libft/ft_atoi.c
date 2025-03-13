/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:16:14 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/04 13:16:17 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	m;
	int	nmb;

	m = 1;
	nmb = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-')
	{
		m *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nmb = nmb * 10;
		nmb += *str - '0';
		str++;
	}
	nmb = nmb * m;
	return (nmb);
}

// int main(void)
// {
// 	printf("%d\n", ft_atoi("-2147483648"));
// 	return(0);
// }