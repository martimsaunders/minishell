/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ttk_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:48:31 by praders           #+#    #+#             */
/*   Updated: 2025/09/29 14:23:26 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_word_and_pipe(t_command **current_cmd,
		t_token *current_token)
{
	if (current_token->type == 0)
	{
		*current_cmd = handle_world_token(*current_cmd, current_token);
		if (!*current_cmd)
			return (0);
	}
	else if (current_token->type == PIPE_TOKEN)
	{
		*current_cmd = ttc_pipe_token(*current_cmd, current_token);
		if (!*current_cmd)
			return (0);
	}
	return (1);
}

static int	handle_redirects(t_command *current_cmd, t_token **current_token)
{
	if ((*current_token)->type == REDIRECT_IN_TOKEN)
	{
		if (!ttc_redirects_in(current_cmd, current_token, 1))
			return (0);
	}
	else if ((*current_token)->type == HEREDOC_TOKEN)
	{
		if (!ttc_redirects_in(current_cmd, current_token, 2))
			return (0);
	}
	else if ((*current_token)->type == REDIRECT_OUT_TOKEN)
	{
		if (!ttc_redirects_out(current_cmd, current_token, 1))
			return (0);
	}
	else if ((*current_token)->type == APPEND_TOKEN)
	{
		if (!ttc_redirects_out(current_cmd, current_token, 2))
			return (0);
	}
	return (1);
}

static int	handle_current_token(t_command **current_cmd,
		t_token **current_token)
{
	if ((*current_token)->type == 0 || (*current_token)->type == PIPE_TOKEN)
	{
		if (!handle_word_and_pipe(current_cmd, *current_token))
			return (0);
	}
	else
	{
		if (!handle_redirects(*current_cmd, current_token))
			return (0);
	}
	return (1);
}

t_command	*tokens_to_commands(t_token *tokens)
{
	t_token		*current_token;
	t_command	*first_cmd;
	t_command	*current_cmd;
	int			index;

	index = 0;
	first_cmd = create_command();
	if (!first_cmd)
		return (mv(1), NULL);
	current_cmd = first_cmd;
	current_token = tokens;
	while (current_token)
	{
		current_token->index = index++;
		if (!handle_current_token(&current_cmd, &current_token))
			return (free_commands(first_cmd), NULL);
		current_token = current_token->next;
	}
	return (first_cmd);
}
