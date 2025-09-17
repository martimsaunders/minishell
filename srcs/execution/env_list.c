/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:37:55 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/17 14:48:14 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void name_fill(t_env *node, char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	node->name = ft_calloc(i + 1, sizeof(char));
	if (!node->name)
		total_exit("malloc() error!!");
	i = 0;
	while (str[i] && str[i] != '=')
	{
		node->name[i] = str[i];
		i++;
	}
	node->name[i] = '\0';
}

void value_fill(t_env *node, char *str)
{
	char *value;
	int i;

	value = ft_strchr(str, '=');
	value++;
	i = 0;
	while (value[i])
		i++;
	node->value = ft_calloc(i + 1, sizeof(char));
	if (!node->value)
		total_exit("malloc() error!!");
	i = 0;
	while (value[i])
	{
		node->value[i] = value[i];
		i++;
	}
	node->value[i] = '\0';
}

t_env *create_env_node(char *str)
{
	t_env *node;
	
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		total_exit("malloc() error!!");
	name_fill(node, str);
	value_fill(node, str);
	node->next = NULL;
	return (node);
}

void t_env_add_back(t_env **list, t_env *node)
{
    t_env *last;

    if (*list == NULL)
		*list = node;
    else
    {
        last = *list;
        while (last->next)
            last = last->next;
        last->next = node;
    }
}

t_env *create_env(char **env)
{
	t_env	*ms_env;
	t_env *node;
	int		i;

	ms_env = NULL;
	i = 0;
	while (env[i])
	{
		node = create_env_node(env[i]);
        t_env_add_back(&ms_env, node);
		i++;
	}
	return (ms_env);
}
