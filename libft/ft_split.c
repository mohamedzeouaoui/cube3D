/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:10:37 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/12 13:10:42 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countword(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**lieson(char **big_str, const char *s, char c)
{
	int	i;
	int	start;
	int	idx;

	idx = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		start = i;
		while (s[i] != c && s[i])
			i++;
		big_str[idx] = ft_substr(s, start, i - start);
		if (big_str[idx] == NULL)
		{
			ft_free(big_str);
			return (NULL);
		}
		idx++;
	}
	return (big_str);
}

char	**ft_split(char const *s, char c)
{
	char	**big_str;
	int		nmbr_word;

	if (!s)
		return (NULL);
	nmbr_word = countword(s, c);
	big_str = malloc(sizeof(char *) * (nmbr_word + 1));
	if (big_str == NULL)
		return (NULL);
	big_str[nmbr_word] = 0;
	big_str = lieson(big_str, s, c);
	return (big_str);
}

// int main(int argc, char const *argv[])
// {
//     char **str;
//     str = ft_split("vvmohamedvv saidevv jawadvv",'v');
//     int i;
//     while (str[i])
//     {
//         printf("\"%s\"\n",str[i]);
//         i++;
//     }
//     ft_free(str);
//     return (0);
// }