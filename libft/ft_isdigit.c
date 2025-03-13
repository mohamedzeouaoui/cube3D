/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:40:24 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/03 18:40:27 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*int main()
{
	char ch;
	printf("Enter a character: ");
	scanf("%c", &ch);

	if (ft_isdigit(ch))
	{
		printf("%c is a digit.\n", ch);
	}
	else
	{
		printf("%c is not a digit.\n", ch);
	}

	return (0);
}*/