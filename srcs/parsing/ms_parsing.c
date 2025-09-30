/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:47:53 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/29 14:46:41 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_quote(t_parse_state *state)
{
	int	quote_type;

	quote_type = is_quote(state->input[state->current]);
	if (quote_type != 0)
	{
		if (state->in_quotes == 0)
			state->in_quotes = quote_type;
		else if (state->in_quotes == quote_type)
			state->in_quotes = 0;
	}
	state->current++;
}

static int	process_space(t_parse_state *state, t_token **token_list)
{
	t_token	*new_token;
	char	*token;
	int		is_quoted;

	is_quoted = 0;
	if (state->current > state->token_start)
	{
		token = extract_token(state, state->token_start, state->current,
				&is_quoted);
		if (!token)
			return (0);
		new_token = create_token(token, 0, is_quoted);
		if (!new_token)
			return (0);
		add_token_list(token_list, new_token);
	}
	while (is_ws(state->input, state->current))
		state->current++;
	state->token_start = state->current;
	return (1);
}

static int	process_operator(t_parse_state *state, t_token **token_list,
		int i_q)
{
	t_token	*new_token;
	char	*token;

	if (state->current > state->token_start)
	{
		token = extract_token(state, state->token_start, state->current, &i_q);
		if (!token)
			return (0);
		new_token = create_token(token, 0, i_q);
		if (!new_token)
			return (0);
		add_token_list(token_list, new_token);
	}
	if ((state->input[state->current] == '<' && state->input[state->current
				+ 1] == '<') || (state->input[state->current] == '>'
			&& state->input[state->current + 1] == '>'))
	{
		if (!process_operator2(state, 2, &new_token))
			return (0);
	}
	else if (!process_operator2(state, 1, &new_token))
		return (0);
	add_token_list(token_list, new_token);
	state->token_start = state->current;
	return (1);
}

static int	process_last_word(t_parse_state *state, t_token **token_list)
{
	char	*token;
	t_token	*new_token;
	int		is_quoted;

	is_quoted = 0;
	if (state->current > state->token_start)
	{
		token = extract_token(state, state->token_start, state->current,
				&is_quoted);
		if (!token)
			return (0);
		new_token = create_token(token, 0, is_quoted);
		if (!new_token)
			return (0);
		add_token_list(token_list, new_token);
	}
	return (1);
}

t_token	*ms_parsing(t_parse_state *state)
{
	t_token	*token_list;

	token_list = NULL;
	while (state->input[state->current])
	{
		if (is_quote(state->input[state->current]))
			process_quote(state);
		else if (is_ws(state->input, state->current) && state->in_quotes == 0)
		{
			if (!process_space(state, &token_list))
				malloc_exit(token_list, state);
		}
		else if (is_op(state->input[state->current]) && state->in_quotes == 0)
		{
			if (!process_operator(state, &token_list, 0))
				malloc_exit(token_list, state);
		}
		else
			state->current++;
	}
	if (!process_last_word(state, &token_list))
		malloc_exit(token_list, state);
	else if (state->in_quotes != 0)
		return (free_token_list(token_list, 1), ft_putstr_fd(ERRQUO, 2), NULL);
	return (remove_empty_tokens(&token_list), token_list);
}
