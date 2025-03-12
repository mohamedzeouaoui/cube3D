/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakhrif <aakhrif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:36:33 by aakhrif           #+#    #+#             */
/*   Updated: 2025/03/11 23:02:51 by aakhrif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_gc_strdup(const char *s)
{
	size_t	len;
	char	*dest;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dest = (char *)gc_malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s, (len + 1));
	return (dest);
}
