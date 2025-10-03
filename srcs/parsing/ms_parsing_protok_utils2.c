/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_protok_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimprazeresaunders <martimprazeresau    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:55 by praders           #+#    #+#             */
/*   Updated: 2025/10/03 14:36:37 by martimpraze      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_dollar_count3(char *raw_token, int *i, int var_start)
{
	if (var_start == (*i) + 1 && (!raw_token[var_start] || is_ws(raw_token,
				var_start) == true))
		return (0);
	else if ((var_start == (*i) + 1 && dq(2) != 0))
		return (0);
	return (1);
}

int	handle_dollar_alloc3(char *raw_token, int *i, int var_start)
{
	if (var_start == (*i) + 1 && (!raw_token[var_start] || is_ws(raw_token,
				var_start) == true))
		return (0);
	else if ((var_start == (*i) + 1 && dq(2) != 0))
		return (0);
	return (1);
}
