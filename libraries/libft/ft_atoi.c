/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:05:58 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/21 12:37:55 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		result;
	char	signal;

	signal = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signal *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (signal * result);
}

/*int	main(void)
{
	printf("atoi = %d, ft_atoi = %d\n", atoi("1242"), ft_atoi("1242"));
	printf("atoi = %d, ft_atoi = %d\n", atoi("-1242"), ft_atoi("-1242"));
	printf("atoi = %d, ft_atoi = %d\n", atoi("-+1242"), ft_atoi("-+1242"));
	printf("atoi = %d, ft_atoi = %d\n", atoi(" \n1242"), ft_atoi(" \n1242"));
	printf("atoi = %d, ft_atoi = %d\n", atoi(" \n1a242"), ft_atoi(" \n1a242"));
	printf("atoi = %d, ft_atoi = %d\n", atoi("2147483648"),
		ft_atoi("2147483648"));
	printf("atoi = %d, ft_atoi = %d\n", atoi("2147483649"),
		ft_atoi("2147483649"));
	return (0);
}*/