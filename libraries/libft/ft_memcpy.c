/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:15:24 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 11:57:20 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*byte;

	if (!dest || !src)
		return (NULL);
	ptr = (unsigned char *)dest;
	byte = (const unsigned char *)src;
	while (n-- > 0)
		*ptr++ = *byte++;
	return (dest);
}

/*int	main(void)
{
	char s[25] = "Ola amigos como estao";
	char dest[25];
	char dest2[25];
	int a[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int b[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int d[15];
	int e[15];
	int i = 0;

	char *l = memcpy(NULL, NULL, 5);
	char *p = ft_memcpy(NULL, NULL, 5);

	printf("memcpy(NULL, NULL, 0): %p\n", l);
	printf("ft_memcpy(NULL, NULL, 0): %p\n", p);

	memcpy(dest, s, sizeof(s));
	ft_memcpy(dest2, s, sizeof(s));
	printf("memcpy = %s, ft_memcpy = %s\n", dest, dest2);

	memcpy(d, a, sizeof(a));
	while (i < 10)
	{
		printf("%d", d[i]);
		i++;
	}
	printf("\n");
	ft_memcpy(e, b, sizeof(b));
	i = 0;
	while (i < 10)
	{
		printf("%d", e[i]);
		i++;
	}
	printf("\n");

	return (0);
}*/