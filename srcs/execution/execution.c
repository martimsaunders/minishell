/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 14:01:14 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_process	*pc(void)
{
	static t_process	pc;

	return (&pc);
}

void	reset_pc(void)
{
	close_fds();
	pc()->cmd = NULL;
	pc()->list_size = 0;
	free(pc()->fd.here_docs);
	pc()->fd.here_docs = 0;
	free(pc()->pid_array);
	pc()->pid_array = 0;
	pc()->processes = 0;
	pc()->path = NULL;
	if (sig_detect)
	{
		sig_detect = 0;
	}
	if (pc()->sigmode == HERE_DOC)
		// write(STDOUT_FILENO, "\n", 1);
		pc()->sigmode = INPUT;
}

int	exit_status_return(void)
{
	int	exit_code;

	if (WIFEXITED(pc()->exit_status))
		exit_code = WEXITSTATUS(pc()->exit_status);
	else if (WIFSIGNALED(pc()->exit_status))
		exit_code = 128 + WTERMSIG(pc()->exit_status);
	else
		exit_code = 1;
	pc()->exit_status = exit_code;
	return (exit_code);
}

int	execution_process(t_command *cmd, char **env)
{
	if (!pc()->ms_env)
		pc()->ms_env = create_env(env);
	pc()->cmd = cmd;
	pc()->list_size = cmd_lstsize(cmd);
	init_fds();
	pc()->exit_status = here_docs_check(cmd);
	if (!sig_detect)
	{
		if (pc()->list_size > 1)
		{
			// pc()->pid_array = ft_calloc(pc()->list_size + 1, sizeof(pid_t));
			// if (!pc()->pid_array)
			// 	total_exit("malloc error!!");
			// pc()->pid_array[pc()->list_size] = -1;
			pc()->exit_status = pipe_command_process(cmd);
		}
		else if (pc()->list_size == 1)
			pc()->exit_status = single_command_process(cmd);
	}
	free_command_list(&cmd);
	reset_pc();
	return (pc()->exit_status);
}

/*
TESTS:
single and multiple exec commands with and without redirects OK
built ins simple commands OK
NOTES:
adicionar varavel enum que diz se estou num proc filho ou pai para o sigint ser executado de acordo
reorganizar codigo geral e implementar saida correta de Ctrl C
*/