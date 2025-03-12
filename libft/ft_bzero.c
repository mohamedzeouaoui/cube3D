/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeouaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:18:28 by mzeouaou          #+#    #+#             */
/*   Updated: 2023/11/04 13:18:30 by mzeouaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
// #include<stdio.h>
// int	main()
// {
// 	char str[]="mohamed";
// 	ft_bzero(str + 3, 1);
// 	printf("%s\n", str);
// 	return(0);
// }