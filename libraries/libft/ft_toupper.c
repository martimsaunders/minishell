/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:57 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:53 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

/*int	main(void)
{
	printf("toupper = %d, ft_toupper = %d\n", toupper('a'), ft_toupper('a'));
	printf("toupper = %d, ft_toupper = %d\n", toupper('1'), ft_toupper('1'));
	printf("toupper = %d, ft_toupper = %d\n", toupper('z'), ft_toupper('z'));
	printf("toupper = %d, ft_toupper = %d\n", toupper(' '), ft_toupper(' '));
	printf("toupper = %d, ft_toupper = %d\n", toupper('*'), ft_toupper('*'));
	return (0);
}*/