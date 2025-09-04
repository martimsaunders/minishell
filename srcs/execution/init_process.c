/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:39:56 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/04 17:05:45 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_process *pc()
{
    static t_process pc;
    return(&pc);
}

void reset_statics()
{
	
}

void init_fds()
{
    pc()->fd.pipe1[0] = -1;
    pc()->fd.pipe1[1] = -1;
    pc()->fd.pipe2[0] = -1;
    pc()->fd.pipe2[1] = -1;
    pc()->fd.current = pc()->fd.pipe2;
	pc()->fd.previous = pc()->fd.pipe1;
}