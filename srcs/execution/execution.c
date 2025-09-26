/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:06:17 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/25 18:28:04 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	pc()->sigmode = INPUT;
}

t_process	*pc(void)
{
	static t_process	pc;

	return (&pc);
}

void	reset_pc(void)
{
	pc()->cmd = NULL;
	pc()->list_size = 0;
	pc()->processes = 0;
	pc()->path = NULL;
	pc()->pid = 0;
	if (g_sig_detect)
		g_sig_detect = 0;
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

int	execution_process(t_command *cmd)
{
	pc()->cmd = cmd;
	pc()->list_size = cmd_lstsize(cmd);
	init_fds();
	here_docs_check(cmd);
	if (!g_sig_detect)
	{
		if (pc()->list_size > 1)
			pc()->exit_status = pipe_command_process(cmd);
		else if (pc()->list_size == 1)
			pc()->exit_status = single_command_process(cmd);
	}
	close_fds();
	free_command_list(&cmd);
	reset_pc();
	return (pc()->exit_status);
}
/*
verificar exit error exit status number
export verificar exit code error
comando absoluto exit codes verificar
testtar mais built ins
norme - ficheiros mais de 5 funcs
refazer folha avl
*/