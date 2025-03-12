/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:16:59 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/04 13:17:02 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	j;

	if (!dst && !src)
		return (NULL);
	if (dst == src || len == 0)
		return (dst);
	if (dst > src && dst - src < (int)len)
	{
		j = len - 1;
		while (j >= 0)
		{
			((unsigned char *)dst)[j] = ((unsigned char *)src)[j];
			j--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

// int	main(void)
// {
// 	char	str[];

// 	str[] = "anas jawad";
// 	ft_memmove(str + 2, str, 4);
// 	printf("%s\n", str);
// 	return (0);
// }
