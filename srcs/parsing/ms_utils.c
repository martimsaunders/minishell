/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:05:56 by praders           #+#    #+#             */
/*   Updated: 2025/09/15 16:35:06 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mv(int set_value)
{
	static int malloc_value;
	if (set_value != 0)
		malloc_value = set_value;
	return (malloc_value);
}