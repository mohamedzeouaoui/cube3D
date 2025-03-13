/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:00:51 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/02 16:00:57 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	else
		return (0);
}

/*
int	main(void)
{
	char	ch;

	ch = 'A';
	if (ft_isalpha(ch))
	{
		printf("%c is an alphabetic character.\n", ch);
	}
	else
	{
		printf("%c is not an alphabetic character.\n", ch);
	}
	return (0);
}
*/