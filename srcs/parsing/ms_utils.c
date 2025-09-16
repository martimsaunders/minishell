/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:05:56 by praders           #+#    #+#             */
/*   Updated: 2025/09/16 16:00:34 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	hd(int set_value)
{
	static int double_quote_value;
	if (set_value != 2)
		double_quote_value = set_value;
	return (double_quote_value);
}

int	dq(int set_value)
{
	static int double_quote_value;
	if (set_value != 2)
		double_quote_value = set_value;
	return (double_quote_value);
}

int	mv(int set_value)
{
	static int malloc_value;
	if (set_value != 0)
		malloc_value = set_value;
	return (malloc_value);
}