/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:02:41 by mzeouaou          #+#    #+#             */
/*   Updated: 2025/02/24 13:02:45 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3D.h"

char	*ft_strcat_edit(char *str, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	str[0] = '\0'; 
	while (str[i])
		i++;
	while (str2[j] != '\0' && str2[j] != '\n' && str2[j] != ' ' && str2[j] != '\t')
	{
		str[i] = str2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_parsing(char *s, int start, int len)
{
	char	*new;
	// int	i;

	if (!s)
		return (NULL);
	while (s[start] == ' ' || s[start] == '\t')
		start++;
	new = (char *)malloc(sizeof(char) * (len - start + 1));
	if (!new)
		return (NULL);
	new = ft_strcat_edit(new, s + start);
    free(s);
	return (new);
}
