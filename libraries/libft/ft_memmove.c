/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:52:50 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 11:57:43 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest || !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
	{
		while (n-- > 0)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n-- > 0)
			*--d = *--s;
	}
	return (dest);
}

/*int	main(void)
{
	char src[] = "ola amigos como estao";
	char src2[] = "ola amigos como estao";
	char dest[20];

	memmove(dest, src, 5);
	ft_memmove(dest, src2, 5);
	printf("%s\n", dest);
	printf("%s\n", dest);
	return (0);
}*/