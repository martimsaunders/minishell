/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimprazeresaunders <martimprazeresau    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:35:35 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/18 19:58:43 by martimpraze      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*newstr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && check_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && check_set(s1[end - 1], set))
		end--;
	newstr = malloc(sizeof(char) * (end - start + 1));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, &s1[start], end - start + 1);
	return (newstr);
}

/*int	main(void)
{
	char *s1 = "O O";
	char *set = "O ";
	char *result;

	result = ft_strtrim(s1, set);
	printf("Resultado: |%s|\n", result);
	free(result);
	return (0);
}*/