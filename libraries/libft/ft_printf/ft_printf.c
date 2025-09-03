/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:36:00 by marvin            #+#    #+#             */
/*   Updated: 2025/05/05 14:50:32 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check(char format)
{
	if (format == 'c' || format == 's' || format == 'p' || format == 'i'
		|| format == 'd' || format == 'u' || format == 'x' || format == 'X'
		|| format == '%')
		return (1);
	return (0);
}

static int	handle_percentage(va_list args, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		count += ft_putadr(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count += ft_putnbr_base(va_arg(args, int), 1, 10, "0123456789");
	else if (format == 'u')
		count += ft_putnbr_base(va_arg(args, unsigned int), 0, 10,
				"0123456789");
	else if (format == 'x')
		count += ft_putnbr_base(va_arg(args, unsigned int), 0, 16,
				"0123456789abcdef");
	else if (format == 'X')
		count += ft_putnbr_base(va_arg(args, unsigned int), 0, 16,
				"0123456789ABCDEF");
	else if (format == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		while (format[i] == '%' && format[i + 1])
			if (check(format[i++ + 1]))
				count += handle_percentage(args, format[i++]);
		if (format[i])
			count += ft_putchar(format[i++]);
	}
	va_end(args);
	return (count);
}
