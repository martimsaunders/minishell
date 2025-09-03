/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:07:45 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 12:00:52 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (n == 0)
		return (0);
	while (i < n && (s1[i] == s2[i] && i < n) && (s1[i] != '\0'
			&& s2[i] != '\0'))
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*int	main(void)
{
	const char *s1 = "Hello";
	const char *s2 = "Helium";

	printf("strncmp: %d, ft_strncmp: %d\n", strncmp(s1, s2, 3), ft_strncmp(s1,
			s2, 3));
	printf("strncmp: %d, ft_strncmp: %d\n", strncmp(s1, s2, 5), ft_strncmp(s1,
			s2, 5));
	printf("strncmp: %d, ft_strncmp: %d\n", strncmp(s1, "Hello", 5),
		ft_strncmp(s1, "Hello", 5));
	return (0);
}*/