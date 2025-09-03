/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:18 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/03 12:02:15 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	chr;
	const char		*last;

	last = NULL;
	chr = c;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == chr)
			last = s;
		s++;
	}
	if (chr == '\0')
		return ((char *)s);
	return ((char *)last);
}

/*int	main(void)
{
	printf("strrchr = %s, ft_strrchr = %s\n", strrchr("ola amigos", 'o'),
		ft_strrchr("ola amigos", 'o'));
	return (0);
}*/