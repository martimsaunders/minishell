/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:39:56 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/05 12:57:40 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_process *pc()
{
    static t_process pc;
    return(&pc);
}

int	cmd_lstsize(t_command *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}