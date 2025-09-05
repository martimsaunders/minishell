/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:37:27 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/05 19:06:38 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void init_fds()
{
    pc()->fd.pipe1[0] = -1;
    pc()->fd.pipe1[1] = -1;
    pc()->fd.pipe2[0] = -1;
    pc()->fd.pipe2[1] = -1;
    pc()->fd.current = pc()->fd.pipe2;
	pc()->fd.previous = pc()->fd.pipe1;
}

void	ft_close(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

void	close_fds()
{
	ft_close(&pc()->fd.previous[0]);
	ft_close(&pc()->fd.previous[1]);
	ft_close(&pc()->fd.current[0]);
	ft_close(&pc()->fd.current[1]);
}