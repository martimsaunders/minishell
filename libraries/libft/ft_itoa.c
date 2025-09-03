/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:27:23 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/17 13:35:42 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_number(long nbr)
{
	size_t	count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		count++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

static char	*ft_putnbr(char *str, size_t space, long n)
{
	size_t	space2;

	space2 = space;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[--space] = (n % 10) + '0';
		n = n / 10;
	}
	str[space2] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	space;
	char	*str;
	long	nbr;

	nbr = n;
	space = count_number(nbr);
	str = malloc(sizeof(char) * (space + 1));
	if (!str)
		return (NULL);
	return (ft_putnbr(str, space, nbr));
}

/*int	main(void)
{
	printf("Resultado: %s\n", ft_itoa(-10));
	printf("Resultado: %s\n", ft_itoa('o'));
	printf("Resultado: %s\n", ft_itoa(2147483647));
	printf("Resultado: %s\n", ft_itoa(-2147483648));
	printf("Resultado: %s\n", ft_itoa(12345));
	return (0);
}*/
