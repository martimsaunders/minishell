/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 10:44:36 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 12:01:51 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big || !little)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while ((big[i + j] != '\0') && big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	const char *haystack = "Hello, World!";
	const char *needle = "World";

	printf("ft_strnstr: %s\n", ft_strnstr(haystack, needle, 12));
	printf("ft_strnstr: %s\n", ft_strnstr(haystack, needle, 5));
	printf("ft_strnstr: %s\n", ft_strnstr(haystack, "", 5));
	printf("ft_strnstr: %s\n", ft_strnstr(haystack, "Hello", 5));
	printf("ft_strnstr: %s\n", ft_strnstr(haystack, "!", 13));

	return (0);
}*/