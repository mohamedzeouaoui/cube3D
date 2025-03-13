/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:20:46 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/04 13:20:48 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lenlit;

	if (big == NULL || little == NULL)
		return (NULL);
	lenlit = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (i + lenlit <= len && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] != '\0')
		{
			j++;
			if (little[j] == '\0')
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}

// int	main()
// {
// 	// ft_strnstr(NULL,"HELLO",0);
// 	ft_strnstr(NULL,NULL,5);
// 	return(0);
// }