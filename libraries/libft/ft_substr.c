/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:45:50 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:52 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
	{
		subs = malloc(1);
		if (!subs)
			return (NULL);
		subs[0] = '\0';
		return (subs);
	}
	if (len > i - start)
		len = i - start;
	subs = malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	ft_strlcpy(subs, &s[start], len + 1);
	return (subs);
}

/*int	main(void)
{
	char *src = "Ola amigos comoa estao";
	char *dst = ft_substr(src, 4, 12);

	printf("Resultado: %s\n", dst);
	return (0);
	// while (s[start] != '\0' && i < space)
	//	subs[i++] = s[start++];
	// subs[i] = '\0';
}*/