/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:43:07 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/22 11:38:20 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

/*int	main(void)
{
	t_list *first;
	t_list *second;
	t_list *new;
	t_list *current;
	t_list *temp;

	first = ft_lstnew("Olo");
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
	new = ft_lstnew("Tudo bem!");
	if (!new)
	{
		free(first);
		free(second);
		printf("Erro\n");
		return (1);
	}
	first->next = second;
	ft_lstadd_back(&first, new);
	current = first;
	while (current)
	{
		printf("Ordem Nó: %s\n", (char *)current->content);
		current = current->next;
	}
	while (first)
	{
		temp = first;
		first = first->next;
		free(temp);
	}
}*/