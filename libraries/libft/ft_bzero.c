/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:14:48 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 11:52:39 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	if (!s)
		return ;
	ptr = (unsigned char *)s;
	while (n-- > 0)
		*ptr++ = '\0';
}

/*int	main(void)
{
	char a[25] = "Ola amigos como estao";
	char b[25] = "Ola amigos como estao";
	int c[15] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int d[15] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i = 0;

	bzero(a, 3);
	ft_bzero(b, 3);
	printf("bzero = %s, ft_bzero = %s\n", a, b);

	for (int e = 0; e < 25; e++)
	{
		printf("%c", a[e] ? a[e] : '.');
	}
	printf ("\n");
	for (int e = 0; e < 25; e++)
	{
		printf("%c", b[e] ? b[e] : '.');
	}
	printf ("\n");
	bzero(c, 20);
	ft_bzero(d, 20);
	while (i < 15)
	{
		printf("%d", c[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < 15)
	{
		printf("%d", d[i]);
		i++;
	}
	printf("\n");
}*/