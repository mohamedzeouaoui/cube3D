/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:18:45 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/23 15:38:49 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return ((void *)p);
}

// #include <stdio.h>
// int main(void)
// {
// 	int i = 2;
// 	ft_bzero(&i, 4);
// 	ft_memset(&i, 197, 1);
// 	ft_memset((char *)&i + 1, 6, 1);
// 	printf("%d", i);
// 	return (0);
// }
