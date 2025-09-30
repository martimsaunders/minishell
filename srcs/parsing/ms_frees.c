/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:02:51 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/29 14:23:20 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_commands(t_command *commands)
{
	t_command	*current;
	t_command	*next;

	current = commands;
	while (current)
	{
		next = current->next;
		free_command(current);
		current = next;
	}
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	if (command->cmd)
		free(command->cmd);
	if (command->args)
	{
		while (command->args[i])
			free(command->args[i++]);
		free(command->args);
	}
	if (command->infiles)
		free_redirects(command->infiles);
	if (command->outfiles)
		free_redirects(command->outfiles);
	free(command);
}

void	free_redirects(t_redirect *redirects)
{
	t_redirect	*current;
	t_redirect	*next;

	current = redirects;
	while (current)
	{
		next = current->next;
		free(current->filename);
		free(current);
		current = next;
	}
}

void	free_args(char **args, int i)
{
	while (i > 0)
		free(args[--i]);
	free(args);
}

void	free_token_list(t_token *head, int i)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	if (i == 1)
		pc()->exit_status = 2;
}
