/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:37:03 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/15 15:41:25 by mateferr         ###   ########.fr       */
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

	token = extract_token(state, state->current, state->current + add);
	if (!token)
		return (0);
	*new_token = create_token(token, 1);
	if (!*new_token)
		return (0);
	state->current += add;
	return (1);
}
