/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:29:16 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 11:58:17 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	byte;

	if (!s)
		return (NULL);
	ptr = (unsigned char *)s;
	byte = (unsigned char)c;
	while (n-- > 0)
		*ptr++ = byte;
	return (s);
}

/*int	main(void)
{
	char s[25] = "Ola amigos como estao";
	int	a[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	i = 0;

	printf("memset = %s, ft_memset = %s\n", memset(s, 'X', 4), ft_memset(s, 'X',
			4));
	memset(a, 1, 16);
	while (i < 15)
	{
			printf("%d", a[i]);
			i++;
	}
	printf("\n");
	ft_memset(a, 1, 16);
	i = 0;
	while (i < 15)
	{
			printf("%d", a[i]);
			i++;
	}
	printf("\n");
	return (0);
}*/