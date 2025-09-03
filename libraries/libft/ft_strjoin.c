/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:45:46 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 15:36:05 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	space;
	char	*str;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen(s1) > (size_t)-1 - ft_strlen(s2) - 1)
		return (NULL);
	space = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (space + 1));
	space = 0;
	if (!str)
		return (NULL);
	while (s1[space])
		str[i++] = s1[space++];
	space = 0;
	while (s2[space])
		str[i++] = s2[space++];
	str[i] = '\0';
	return (str);
}

/*int main(void)
{
	char *s1 = "Hello";
	char *s2 = " World!";

	printf("Resultado: %s\n", ft_strjoin(s1, s2));
	return (0);
}*/