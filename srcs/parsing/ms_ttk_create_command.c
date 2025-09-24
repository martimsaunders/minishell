/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ttk_create_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:27:33 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/24 14:02:20 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_args(t_token *start)
{
	t_token	*current;
	int		size;

	size = 0;
	current = start;
	while (current && current->type != PIPE_TOKEN)
	{
		if (current->type == 0)
			size++;
		else
		{
			current = current->next;
			if (current && current->type == 0)
				current = current->next;
			continue ;
		}
		current = current->next;
	}
	return (size);
}

static char	**fill_args_array(char **args, t_token *start, int size, int i)
{
	t_token	*current;

	current = start;
	while (current && current->type != PIPE_TOKEN)
	{
		if (current->type == 0)
		{
			args[i] = ft_strdup(current->value);
			if (!args[i])
				return (mv(1), free_args(args, i), NULL);
			i++;
		}
		else
		{
			current = current->next;
			if (current && current->type == 0)
				current = current->next;
			continue ;
		}
		current = current->next;
	}
	args[size] = NULL;
	return (args);
}

char	**build_args_array(t_token *start)
{
	char	**args;
	int		size;

	size = count_args(start);
	args = malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (mv(1), NULL);
	args = fill_args_array(args, start, size, 0);
	if (!args)
		return (NULL);
	return (args);
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (mv(1), NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	return (cmd);
}

int	add_redirect(t_redirect **head, char *filename, int is_quoted,
		int is_append)
{
	t_redirect	*new_redirect;
	t_redirect	*current;

	new_redirect = malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (mv(1), 0);
	ft_memset(new_redirect, 0, sizeof(t_redirect));
	new_redirect->filename = ft_strdup(filename);
	if (!new_redirect->filename)
		return (mv(1), free(new_redirect), 0);
	new_redirect->type = is_append;
	new_redirect->expand = is_quoted;
	if (!*head)
	{
		*head = new_redirect;
		return (1);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redirect;
	return (1);
}
