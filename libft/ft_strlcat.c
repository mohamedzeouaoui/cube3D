/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:21:40 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/22 09:32:40 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;

	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	j = dstlen;
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	while (src[i] != '\0' && i < dstsize - dstlen - 1)
	{
		((char *)dst)[j] = ((char *)src)[i];
		j++;
		i++;
	}
	((char *)dst)[j] = '\0';
	return (dstlen + srclen);
}
