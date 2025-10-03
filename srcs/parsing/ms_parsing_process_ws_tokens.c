/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_process_ws_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:55:00 by praders           #+#    #+#             */
/*   Updated: 2025/10/03 14:30:08 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	add_split_tokens(t_token **token_list, char **split, int is_quoted)
{
	int		j;
	t_token	*new_token;

	j = 0;
	while (split[j])
	{
		new_token = create_token(split[j], 0, is_quoted);
		if (!new_token)
			return (ms_free_split(split, j), 0);
		add_token_list(token_list, new_token);
		j++;
	}
	return (free(split), 1);
}

static	int	add_single_token(t_token **token_list, char *token, int is_quoted)
{
	t_token *new_token;

	new_token = create_token(token, 0, is_quoted);
	if (!new_token)
		return (0);
	add_token_list(token_list, new_token);
	return (1);
}

int	process_and_add_token(t_parse_state *state, t_token **token_list, int start, int finish)
{
	char	*token;
	int		error;
	char	**split;
	int		is_quoted;

	is_quoted = 0;
	token = extract_token(state, start, finish, &is_quoted);
	if (!token)
		return (0);
	error = 0;
	split = split_token_ws(token, &error, is_quoted);
	if (error)
		return (free(token), 0);
	if (split && is_quoted == 0)
		return (free (token), add_split_tokens(token_list, split, is_quoted));
	else
		return (add_single_token(token_list, token, is_quoted));
}
