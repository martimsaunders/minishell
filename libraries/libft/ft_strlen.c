/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:16:13 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/23 18:15:58 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	if (!c)
		return (0);
	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

/*int	main(void)
{
	char *c = "123";

	printf("strlen = %d, ft_strlen = %d\n", strlen(c), ft_strlen(c));
	return (0);
}*/