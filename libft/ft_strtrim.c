/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:10:17 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/12 13:10:20 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	test(char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	int		idx;
	char	*str;

	idx = 0;
	while (test(s1[idx], set) == 1)
		idx++;
	start = idx;
	if (s1[start] == '\0')
	{
		str = ft_strdup("");
		return (str);
	}
	while (s1[idx] != '\0')
		idx++;
	idx--;
	while (test(s1[idx], set) == 1)
		idx--;
	len = idx - start + 1;
	str = ft_substr(s1, start, len);
	return (str);
}

// int main()
// {
//     char *str;
//     str = ft_strtrim("zxcvmohamedxczeouaouizxc", "zxcv");
//     printf("%s\n", str);
//     free(str);
//     return (0);
// }
