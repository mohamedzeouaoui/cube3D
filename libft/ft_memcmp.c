/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:21:18 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/04 13:21:21 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*l;
	size_t			i;

	i = 0;
	p = (unsigned char *)s1;
	l = (unsigned char *)s2;
	while (i < n)
	{
		if (p[i] != l[i])
		{
			return (p[i] - l[i]);
		}
		i++;
	}
	return (0);
}
