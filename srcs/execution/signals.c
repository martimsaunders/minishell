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
        while (pc()->pid_array[i] != -1)
            kill(pc()->pid_array[i++], SIGINT);
    }
}

void init_signals(int process)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    if (process == 1)
        sa.sa_handler = sig_handler;
    else if (process == 2)
        sa.sa_handler = SIG_DFL;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}