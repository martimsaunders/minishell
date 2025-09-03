/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:44:28 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:50 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*static char	transform(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32 + i);
	return (c + i);
}

int	main(void)
{
	char *s = "ab3de";
	char *result;

	result = ft_strmapi(s, transform);
	printf("String original: %s\n", s);
	printf("String transformada: %s\n", result);
	free(result);
	return (0);
}*/