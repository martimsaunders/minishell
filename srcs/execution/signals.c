/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:04:02 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/02 11:23:18 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			g_sig_detect = 0;

void	sig_handler(int sig)
{
	(void)sig;
	g_sig_detect = 1;
	if (pc()->sigmode == INPUT)
	{
		pc()->exit_status = 130;
		g_sig_detect = 0;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (pc()->sigmode == EXECVE)
		write(STDOUT_FILENO, "\n", 1);
}

static void	here_doc_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	pc()->exit_status = 130;
	process_exit();
}

static void	execve_handler(int sig)
{
	(void)sig;
	pc()->exit_status = 131;
	process_exit();
}

void	init_signals_here_doc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = here_doc_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signals_execve(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = execve_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	signal(SIGINT, SIG_DFL);
}
