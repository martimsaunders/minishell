/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:24:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 14:01:20 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	total_exit(char *msg)
{
	int	i;

	perror(msg);
	if (pc()->fd.here_docs)
	{
		i = 0;
		while (pc()->fd.here_docs[i] != -1)
			close(pc()->fd.here_docs[i++]);
		free(pc()->fd.here_docs);
	}
	if (pc()->pid_array)
		free(pc()->pid_array);
	if (pc()->path)
		free(pc()->path);
	if (pc()->ms_env)
		delete_t_env_list(&pc()->ms_env);
	close_fds();
	if (pc()->cmd)
		free_command_list(&pc()->cmd);
	exit(1);
}

void	free_redirect_list(t_redirect **list)
{
	t_redirect	*rdt;
	t_redirect	*node;

	if (!list)
		return ;
	rdt = *list;
	while (rdt)
	{
		node = rdt;
		free(rdt->filename);
		rdt = rdt->next;
		free(node);
	}
	*list = NULL;
}

void	free_command_list(t_command **list)
{
	t_command	*cmd;
	t_command	*node;

	if (!list)
		return ;
	cmd = *list;
	while (cmd)
	{
		node = cmd;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
			free_array(cmd->args);
		if (cmd->infiles)
			free_redirect_list(&cmd->infiles);
		if (cmd->outfiles)
			free_redirect_list(&cmd->outfiles);
		cmd = cmd->next;
		free(node);
	}
	*list = NULL;
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}
