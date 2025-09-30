/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:35:12 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/30 16:35:14 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_lstsize(t_command *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

void	delete_t_env_list(t_env **list)
{
	t_env	*node;

	while (*list)
	{
		node = *list;
		free((*list)->name);
		free((*list)->value);
		*list = (*list)->next;
		free(node);
	}
	*list = NULL;
}

int	update_env(char *name, char *value)
{
	t_env	*node;
	size_t	size;
	char	*temp;

	if (!value)
		return (1);
	if (!t_env_has_name(name))
		return (1);
	size = ft_strlen(name);
	node = pc()->ms_env;
	while (node && ft_strncmp(node->name, name, size) != 0)
		node = node->next;
	if (node)
	{
		temp = node->value;
		node->value = ft_strdup(value);
		free(temp);
		if (!node->value)
			total_exit("malloc_error!!");
		return (0);
	}
	return (1);
}

void	remove_env(char *name)
{
	t_env	*previous;
	t_env	*node;
	size_t	size;

	size = ft_strlen(name);
	node = pc()->ms_env;
	if (ft_strncmp(node->name, name, size) == 0)
		pc()->ms_env = node->next;
	else
	{
		while (node)
		{
			if (ft_strncmp(node->name, name, size) == 0)
			{
				previous->next = node->next;
				break ;
			}
			previous = node;
			node = node->next;
		}
	}
	free(node->name);
	free(node->value);
	free(node);
}

char	*t_env_find_value(char *name)
{
	t_env	*node;
	size_t	size;

	if (!*name)
		return (NULL);
	size = ft_strlen(name);
	node = pc()->ms_env;
	while (node && ft_strncmp(name, node->name, size + 1) != 0)
		node = node->next;
	if (node)
		return (node->value);
	return (NULL);
}
