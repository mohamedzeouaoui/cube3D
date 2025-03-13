/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:09:06 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/12 13:09:14 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*nstr;
	size_t	lng;
	size_t	i;

	if (s == NULL)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s = s + start;
	lng = 0;
	while (s[lng] != '\0' && len > lng)
		lng++;
	nstr = gc_malloc(sizeof(char) * (lng + 1));
	if (nstr == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0' && len > i)
	{
		nstr[i] = s[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

// int main()
// {
//     const char *originalString = "This is a test string";
//     unsigned int start = 6;
//     size_t length = 8;

//     char *substring = ft_substr(originalString, start, length);

//     if (substring != NULL)
//     {
//         printf("Original String: %s\n", originalString);
//         printf("Substring: %s\n", substring);
//         free(substring);  // Don't forget to free the allocated memory
//     }
//     else
//     {
//         printf("Error: Unable to allocate memory for substring.\n");
//     }

//     return (0);
// }