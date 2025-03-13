/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:14:35 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/29 13:57:42 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	if (size != 0 && nmemb != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(size * nmemb);
	if (ptr == NULL)
	{
		return (0);
	}
	ft_bzero((void *)ptr, nmemb * size);
	return ((void *)ptr);
}

// #include <stdio.h>

// int main(void)
// {
// 	char *str = calloc(2, 20);
// 	if (str == NULL)
// 		printf("NULL");
// 	return (0);
// }
