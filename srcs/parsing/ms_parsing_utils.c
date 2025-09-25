/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:37:03 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/25 14:51:28 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char c)
{
	if (c == '\"')
		return (2);
	else if (c == '\'')
		return (1);
	return (0);
}

bool	is_ws(char *str, int i)
{
	if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		return (true);
	return (false);
}

int	is_op(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '|')
		return (1);
	return (0);
}

int	process_operator2(t_parse_state *state, int add, t_token **new_token)
{
	char	*token;
	int		is_quoted;

	is_quoted = 0;
	token = extract_token(state, state->current, state->current + add,
			&is_quoted);
	if (!token)
		return (0);
	if (ft_strncmp(token, "<<", 3) == 0)
		hd(1);
	*new_token = create_token(token, 1, is_quoted);
	if (!*new_token)
		return (0);
	state->current += add;
	return (1);
}
