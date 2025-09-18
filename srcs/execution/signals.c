/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:12:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/18 17:43:10 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sig_handler(int sig)
{
    if (sig == SIGINT)
        total_exit(NULL);
    else if (sig == SIGQUIT)
        return ;
}

void init_signals()
{
    sigset_t set;
    
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    signal(SIGINT, &sig_handler);
    signal(SIGQUIT, &sig_handler);
}