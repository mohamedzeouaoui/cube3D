/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:22:02 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/04 13:22:04 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	lens;

	lens = ft_strlen(s);
	while (lens >= 0)
	{
		if (s[lens] == (char)c)
			return (&((char *)s)[lens]);
		lens--;
	}
	return (NULL);
}
