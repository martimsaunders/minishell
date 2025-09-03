/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:20:02 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 11:54:14 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	if (!s1 || !s2)
		return (-1);
	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	while (0 < n--)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
	}
	return (0);
}

/*int	main(void)
{
	const char *s1 = "Hello";
	const char *s2 = "Helium";

	printf("memcmp: %d, ft_memcmp: %d\n", memcmp(s1, s2, 3), ft_memcmp(s1, s2,
			3));
	printf("memcmp: %d, ft_memcmp: %d\n", memcmp(s1, s2, 5), ft_memcmp(s1, s2,
			5));
	printf("memcmp: %d, ft_memcmp: %d\n", memcmp(s1, "Hello", 5), ft_memcmp(s1,
			"Hello", 5));
	return (0);
}*/