/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/04 17:32:23 by mateferr         ###   ########.fr       */
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
		pc()->args = cmd->args;
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

char **create_arg(char *cmd)
{
	int n_arg = 0;
	char **arg = ft_calloc(n_arg + 2, sizeof(char *));
	int i = 0;
	arg[i++] = ft_strdup(cmd);
	// while(n_arg--)
	// {
		
	// }
	arg[i] = NULL;
	return arg;
}

t_command *fill_list()
{
	t_command *node;
	node = ft_calloc(1, sizeof(t_command));
	node->cmd = ft_strdup("cat");
	node->args = create_arg(node->cmd);
	node->infile = ft_strdup("a");
	node->outfiles = NULL;
	node->next = NULL;
	return(node);
}

int main(int ac, char **av, char **env) 
{
	int ret = execve_process(fill_list(), env);
	(void)ac;
	(void)av;
	return ret;
}
/*
NOTES:
execussao com e sem redirect de infile funciona
outfile - not tested
free e close final para erro
*/