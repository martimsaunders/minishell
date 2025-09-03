/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:59:24 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:35 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((ft_isdigit(c) || ft_isalpha(c)));
}

/*int	main(void)
{
	char c = 'A';

	printf("isalnum = %d, ft_isalnum = %d\n", isalnum(c), ft_isalnum(c));
	return (0);
}*/