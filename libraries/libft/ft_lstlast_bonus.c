/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:24:19 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/17 10:03:51 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*int	main(void)
{
	t_list *first;
	t_list *second;
	t_list *third;
	t_list	*print;
	t_list	*temp;

	first = ft_lstnew("Ola");
	if (!first)
	{
		printf("Erro\n");
		return (1);
	}
	second = ft_lstnew("Adeus");
	if (!second)
	{
		free(first);
		printf("Erro\n");
		return (1);
	}
	third = ft_lstnew("Final");
	if (!third)
	{
		free(first);
		free(second);
		printf("Erro\n");
		return (1);
	}
	first->next = second;
	second->next = third;
	print = ft_lstlast(first);
	printf("Node: %s\n", (char *)print->content);
	while (first)
	{
		temp = first;
		first = first->next;
		free (temp);
	}
	return (0);
}*/