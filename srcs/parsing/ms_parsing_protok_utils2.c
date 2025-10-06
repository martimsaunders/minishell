/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_protok_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:55 by praders           #+#    #+#             */
/*   Updated: 2025/10/06 20:28:38 by praders          ###   ########.fr       */
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

int	check_numandplica(char *raw_token, int *i)
{
	int	var_start;

	var_start = (*i) + 1;
	if (dq(2) != 1)
	{
		if (raw_token[var_start] && (is_quote(raw_token[var_start])
				|| (!ft_isalpha(raw_token[var_start])
					&& raw_token[var_start] != '_')))
		{
			if (is_quote(raw_token[var_start]))
				(*i) += 1;
			else
				(*i) += 2;
			return (0);
		}
	}
	return (1);
}
