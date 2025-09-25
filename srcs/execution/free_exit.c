/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:04:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/25 11:04:44 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	total_exit(char *msg)
{
	perror(msg);
	close_fds();
	if (pc()->path)
		free(pc()->path);
	if (pc()->ms_env)
		delete_t_env_list(&pc()->ms_env);
	if (pc()->cmd)
		free_command_list(&pc()->cmd);
	clear_history();
	exit(1);
}

void	process_exit(void)
{
	close(0);
	close(1);
	close_fds();
	if (pc()->path)
		free(pc()->path);
	pc()->path = NULL;
	if (pc()->ms_env)
		delete_t_env_list(&pc()->ms_env);
	free_command_list(&pc()->cmd);
	clear_history();
	exit(pc()->exit_status);
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
		ft_close(&cmd->hd_fd);
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
