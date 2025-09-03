/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:04:28 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/17 10:04:03 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*int	main(void)
{
	t_list *first;
	t_list *new_node;
	t_list *current;
	t_list *temp;

	first = ft_lstnew("Segundo nó!");
	if (!first)
	{
		printf("Erro\n");
		return (1);
	}
	new_node = ft_lstnew("Primeiro nó!");
	if (!new_node)
	{
		free(first);
		printf("Erro\n");
		return (1);
	}
	ft_lstadd_front(&first, new_node);
	current = first;
	while (current)
	{
		printf("Current: %s\n", (char *)current->content);
		current = current->next;
	}
	while (first)
	{
		temp = first;
		first = first->next;
		free(temp);
	}
	return (0);
}*/