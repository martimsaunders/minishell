/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:12:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/23 15:01:01 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int sig_detect = 0;

static void sig_handler(int sig)
{
    (void)sig;
    sig_detect = 1;
    if (pc()->sigmode == INPUT)
    {
        sig_detect = 0;
        write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (pc()->sigmode == HERE_DOC)
    {
        pc()->sigmode = SIGNAL;
    }
    else if (pc()->sigmode == EXECVE)
    {
        pc()->sigmode = SIGNAL;
    }
}

void init_signals()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
    pc()->sigmode = INPUT;
}
