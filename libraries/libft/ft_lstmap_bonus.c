/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimprazeresaunders <martimprazeresau    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:31:35 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/18 17:58:57 by martimpraze      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/*void	*duplicate_content(void *content)
{
	return (ft_strdup((char *)content));
}

void	delete_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list *original_list;
	t_list *new_list;
	t_list *current;

	original_list = ft_lstnew(ft_strdup("Node1"));
	ft_lstadd_back(&original_list, ft_lstnew(ft_strdup("Node2")));
	ft_lstadd_back(&original_list, ft_lstnew(ft_strdup("Node3")));
	new_list = ft_lstmap(original_list, duplicate_content, delete_content);
	printf("Lista original:\n");
	current = original_list;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	printf("\nNova lista:\n");
	current = new_list;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	ft_lstclear(&original_list, delete_content);
	ft_lstclear(&new_list, delete_content);

	return (0);
}*/