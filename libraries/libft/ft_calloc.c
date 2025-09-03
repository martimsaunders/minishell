/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:27:53 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/21 12:46:32 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

/*int	main(void)
{
	int *arr;
	int *arr2;
	size_t n = 5;
	size_t i = 0;

	arr = (int *)ft_calloc(n, sizeof(int));
	if (!arr)
	{
		printf("Erro ao alocar memória\n");
		return (1);
	}
	while (i < n)
	{
		printf("arr[%zu] = %d\n", i, arr[i]);
		i++;
	}
	free(arr);

	i = 0;
	arr2 = (int *)calloc(n, sizeof(int));
	if (!arr2)
	{
		printf("Erro ao alocar memória\n");
		return (1);
	}
	while (i < n)
	{
		printf("arr[%zu] = %d\n", i, arr2[i]);
		i++;
	}
	free(arr2);

	return (0);
}*/