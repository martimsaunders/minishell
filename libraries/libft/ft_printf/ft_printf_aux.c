/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:35:22 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/30 12:57:45 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	write(1, &uc, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[count])
		ft_putchar(str[count++]);
	return (count);
}

int	ft_putnbr_base(unsigned long long n, int is_signed, int base, char *digits)
{
	int	count;

	count = 0;
	if (is_signed && (long long)n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	if (n >= (unsigned long long)base)
		count += ft_putnbr_base(n / base, 0, base, digits);
	return (count += ft_putchar(digits[n % base]));
}

int	ft_putadr(void *ptr)
{
	int					count;
	unsigned long long	adr;

	adr = (unsigned long long)(size_t)ptr;
	count = 0;
	if (!adr)
		count += ft_putstr("(nil)");
	else
	{
		count += ft_putstr("0x");
		count += ft_putnbr_base(adr, 0, 16, "0123456789abcdef");
	}
	return (count);
}
