/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:40:05 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/17 14:10:45 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		if (lst->content)
			f(lst->content);
		lst = lst->next;
	}
}

/*void	f(void *content)
{
	int		i;
	char	*str;

	i = 0;
	if (!content)
		return ;
	str = (char *)content;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			str[i] = 'N';
		i++;
	}
}

int	main(void)
{
	t_list *second;
	t_list *first;
	t_list *current;
	t_list *temp;

	first = ft_lstnew(ft_strdup("O23la"));
	if (!first)
	{
		printf("Erro\n");
		return (1);
	}
	second = ft_lstnew(ft_strdup("Ad23eus"));
	if (!second)
	{
		free (first->content);
		free(first);
		printf("Erro\n");
		return (1);
	}
	first->next = second;
	ft_lstiter(first, f);
	current = first;
	while (current)
	{
		printf("Nó atual: %s\n", (char *)current->content);
		current = current->next;
	}
	while (first)
	{
		temp = first;
		free (first->content);
		first = first->next;
		free(temp);
	}
	return (0);
}*/