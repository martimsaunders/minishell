/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:02:28 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:49 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (src[i])
		i++;
	if (size > 0)
	{
		while (*src != '\0' && j++ < size - 1)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (i);
}

/*int main(void)
{
	char	src[] = "Ola amigos como estas";
	char	dst[15];
	int	i = ft_strlcpy(dst, src, 4);

	printf("size = %d, dst = %s\n", i, dst);
	return (0);
}*/