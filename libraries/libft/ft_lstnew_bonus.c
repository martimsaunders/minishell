/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:01:48 by mprazere          #+#    #+#             */
/*   Updated: 2025/04/17 10:04:25 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*int	main(void)
{
	t_list *node;
	int a[3] = {1, 2, 3};
	
	node = ft_lstnew("Ola amigos");
	if (node)
	{
		printf("Conteúdo do nó: %s\n", (char *)node->content);
		free(node);
	}
	node = ft_lstnew(a);
	if (node)
	{
		int *arr = (int *)node->content;
		printf("Conteúdo do nó: %d, %d, %d\n", arr[0], arr[1], arr[2]);
		free(node);
	}
	return (0);
}*/