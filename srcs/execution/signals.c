/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:12:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 14:01:52 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			sig_detect = 0;

static void	sig_handler(int sig)
{
	(void)sig;
	sig_detect = 1;
	if (pc()->sigmode == INPUT)
	{
		pc()->exit_status = 130;
		sig_detect = 0;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (pc()->sigmode == EXECVE)
	{
		write(STDOUT_FILENO, "\n", 1);
		// pc()->sigmode = SIGNAL;
	}
}

void	here_doc_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	// rl_redisplay();
	pc()->exit_status = 130;
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

void	execve_handler(int sig)
{
	(void)sig;
	// write(STDOUT_FILENO, "^\\Quit (core dumped)\n", 21);
	pc()->exit_status = 131;
	process_exit();
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
