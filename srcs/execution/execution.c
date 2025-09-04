/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/04 13:21:04 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execve_process(t_command *cmd, char **env)
{
	t_command *node;
	
	node = cmd;
	init_fds();
	while (node)
	{
		pc()->args = arg_join_front(cmd->args, cmd->cmd);
		pc()->path = cmd_path(cmd->cmd);
		pipex_process(cmd, env);
		free(pc()->path);
		free_array(pc()->args);
		node = node->next;
	}
	waitpid(pc()->pid, &pc()->exit_status, 0);
	pc()->processes--;
	while (pc()->processes--)
		wait(NULL);	
	return (exit_status_return());
}

t_command *fill_list()
{
	t_command *node;
	node = ft_calloc(1, sizeof(t_command));
	node->cmd = ft_strdup("ls");
	node->args = NULL;
	node->infile = NULL;
	node->outfiles = NULL;
	node->next = NULL;
	return(node);
}

int main(int ac, char **av, char **env) //criar lista e testar. verificar erro ls comando invalido
{
	int ret = execve_process(fill_list(), env);
	(void)ac;
	(void)av;
	return ret;
}