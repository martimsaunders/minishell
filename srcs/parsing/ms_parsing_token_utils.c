/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_token_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:34:29 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/15 15:41:23 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_token_size(char *raw_token, int in_single_quote,
		int in_double_quote)
{
	int		i;
	int		size;
	char	c;

	size = 0;
	i = 0;
	while (raw_token[i])
	{
		c = raw_token[i];
		if (c == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (c == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (c == '$' && !in_single_quote)
		{
			if (!handle_dollar_count(raw_token, &i, &size))
				return (-1);
			continue ;
		}
		else
			size++;
		i++;
	}
	return (size);
}

static char	*process_token(char *raw_token)
{
	char	*token;
	int		size;

	size = count_token_size(raw_token, 0, 0);
	if (size == -1)
		return (NULL);
	token = malloc(size + 1);
	if (!token)
		return (NULL);
	size = 0;
	if (!process_loop(raw_token, token, &size, 0))
		return (free(token), NULL);
	token[size] = '\0';
	return (token);
}

char	*extract_token(t_parse_state *state, int start, int finish)
{
	char	*raw_token;
	char	*token;
	int		len;

	len = finish - start;
	raw_token = malloc(len + 1);
	if (!raw_token)
		return (NULL);
	ft_strlcpy(raw_token, &state->input[start], len + 1);
	token = process_token(raw_token);
	if (!token)
		return (free(raw_token), NULL);
	return (free(raw_token), token);
}

t_token	*create_token(char *value, int type)
{
	t_token	*new_token;

	if (type == 1)
	{
		if (ft_strncmp(value, "|", 2) == 0)
			type = PIPE_TOKEN;
		else if (ft_strncmp(value, "<", 2) == 0)
			type = REDIRECT_IN_TOKEN;
		else if (ft_strncmp(value, ">", 2) == 0)
			type = REDIRECT_OUT_TOKEN;
		else if (ft_strncmp(value, "<<", 3) == 0)
			type = HEREDOC_TOKEN;
		else if (ft_strncmp(value, ">>", 3) == 0)
			type = APPEND_TOKEN;
	}
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (free(value), NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
		return (free(value), free(new_token), NULL);
	new_token->type = type;
	new_token->next = NULL;
	return (free(value), new_token);
}

void	add_token_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	current = *head;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_token;
}
