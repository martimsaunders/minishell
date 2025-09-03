/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:36:10 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 11:57:27 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		byte;

	if (!s)
		return (NULL);
	byte = (unsigned char)c;
	ptr = (const unsigned char *)s;
	while (0 < n--)
	{
		if (*ptr == byte)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}

/*int	main(void)
{
	const char *s1 = "Hello";

	printf("memchr: %s, ft_memchr: %s\n", memchr(s1, 'l', 3), ft_memchr(s1, 'l',
			3));
	printf("memchr: %s, ft_memchr: %s\n", memchr(s1, 'l', 5), ft_memchr(s1, 'l',
			5));
	printf("memchr: %s, ft_memchr: %s\n", memchr(s1, 'a', 5), ft_memchr(s1, 'a',
			5));
	printf("memchr: %s, ft_memchr: %s\n", memchr(s1, 'a', 0), ft_memchr(s1, 'a',
				0));
	printf("memchr: %s, ft_memchr: %s\n", memchr(s1, 'H', 1), ft_memchr(s1, 'H',
					1));
	return (0);
}*/