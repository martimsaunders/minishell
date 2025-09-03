/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:21:40 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:52 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*int	main(void)
{
	printf("tolower = %d | ft_tolower = %d\n", tolower('A'), ft_tolower('A'));
	printf("tolower = %d | ft_tolower = %d\n", tolower('Z'), ft_tolower('Z'));
	printf("tolower = %d | ft_tolower = %d\n", tolower('a'), ft_tolower('a'));
	printf("tolower = %d | ft_tolower = %d\n", tolower('2'), ft_tolower('2'));
	printf("tolower = %d | ft_tolower = %d\n", tolower(' '), ft_tolower(' '));
	printf("tolower = %d | ft_tolower = %d\n", tolower('*'), ft_tolower('*'));
	return (0);
}*/