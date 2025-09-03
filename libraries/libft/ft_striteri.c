/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:31:35 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:46 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*void	to_uppercase(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c -= 32 + i;
}

int	main(void)
{
	char str[] = "hello world";

	printf("Antes: %s\n", str);
	ft_striteri(str, to_uppercase);
	printf("Depois: %s\n", str);

	return (0);
}*/