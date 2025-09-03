/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:41:33 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/17 16:26:20 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*delete;
	t_list	*temp;

	if (!lst || !del)
		return ;
	delete = *lst;
	while (delete)
	{
		temp = delete;
		del(delete->content);
		delete = delete->next;
		free(temp);
	}
	*lst = NULL;
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
	ft_lstclear(&first, del);
	if (!first)
	{
		printf("Nó Limpo\n");
		return (0);
	}
	else
	{
		free(first);
		free(second);
		printf("Erro: Lista não foi limpa corretamente\n");
		return (1);
	}
}*/