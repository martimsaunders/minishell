/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:49:52 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 12:31:48 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dpl;

	i = ft_strlen(s);
	dpl = malloc(sizeof(char) * (i + 1));
	if (!dpl)
		return (NULL);
	ft_memcpy(dpl, s, i + 1);
	return (dpl);
}

/*int	main(void)
{
	char *src = "Ola amigos como estao";
	char *cpy = strdup(src);
	char *cpy2 = ft_strdup(src);

	printf("strdup = %s, ft_strdup = %s\n", cpy, cpy2);
	return (0);
}*/