/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:12:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/22 18:15:38 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int sigint_detected = 0;

static void sig_handler(int sig)
{
    int i;
    
    (void)sig;
    sigint_detected = 1;
    i = 0;
    if (pc()->pid_array)
    {
        printf("TRY KILL\n");
        while (pc()->pid_array[i] != -1)
            kill(pc()->pid_array[i++], SIGINT);
    }
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void init_signals()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}