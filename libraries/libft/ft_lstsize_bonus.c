/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:53:09 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/17 10:03:46 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/*int	main(void)
{
	t_list	*first;
	t_list	*second;
	t_list	*third;
	t_list	*temp;

	first = ft_lstnew("OOO");
	if (!first)
	{
		printf("Erro\n");
		return (1);
	}
	second = ft_lstnew("000");
	if (!second)
	{
		free(first);
		printf("Erro\n");
		return (1);
	}
	third = ft_lstnew("000");
	if (!third)
	{
		free(first);
		free(second);
		printf("Erro\n");
		return (1);
	}
	first->next = second;
	second->next = third;
	printf("Size: %d\n", ft_lstsize(first));
	while (first)
	{
		temp = first;
		first = first->next;
		free(temp);
	}
	return (0);
}*/