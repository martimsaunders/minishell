/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:48:12 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/21 16:42:43 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = 0;
	len_src = 0;
	while (dst[len_dst])
		len_dst++;
	while (src[len_src])
		len_src++;
	if (size <= len_dst)
		return (len_src + size);
	i = 0;
	while (src[i] != '\0' && (len_dst + i) < size - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

/*int	main(void)
{
	char src[] = "ola amigos";
	char dst[20] = "como";
	int i = ft_strlcat(dst, src, 0);
	char src2[] = "ola amigos";
	char dst2[20] = "como";
	int a = strlcat(dst2, src2, 0);

	printf("tamanho = %d, dst = %s\n", i, dst);
	printf("tamanho = %d, dst2 = %s\n", a, dst2);
	return (0);
}*/