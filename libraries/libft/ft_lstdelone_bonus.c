/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:05:28 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/17 14:10:26 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*void	del(void *content)
{
	if (!content)
		return ;
	free(content);
}

int	main(void)
{
	t_list *second;
	t_list *first;
	t_list *current;
	t_list *temp;

	first = ft_lstnew(ft_strdup("Ola"));
	if (!first)
	{
		printf("Erro\n");
		return (1);
	}
	second = ft_lstnew(ft_strdup("Adeus"));
	if (!second)
	{
		free(first);
		printf("Erro\n");
		return (1);
	}
	first->next = second;
	ft_lstdelone(second, del);
	first->next = NULL;
	current = first;
	while (current)
	{
		printf("Nó atual: %s\n", (char *)current->content);
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