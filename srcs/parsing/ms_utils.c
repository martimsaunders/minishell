/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:05:56 by praders           #+#    #+#             */
/*   Updated: 2025/09/30 15:09:15 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	hd(int set_value)
{
	static int	here_doc_value;

	if (set_value != 2)
		here_doc_value = set_value;
	return (here_doc_value);
}

int	dq(int set_value)
{
	static int	double_quote_value;

	if (set_value != 2)
		double_quote_value = set_value;
	return (double_quote_value);
}

int	mv(int set_value)
{
	static int	malloc_value;

	if (set_value != 0)
		malloc_value = set_value;
	return (malloc_value);
}

void	remove_empty_tokens(t_token **token_list)
{
	t_token	*current;
	t_token	*prev;
	t_token	*temp;

	current = *token_list;
	prev = NULL;
	while (current)
	{
		if (current->value[0] == '\0' && current->is_quoted != 1)
		{
			temp = current;
			current = current->next;
			if (prev)
				prev->next = current;
			else
				*token_list = current;
			free(temp->value);
			free(temp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

int	check_numandplica(char *raw_token, int *i)
{
	int	var_start;

	var_start = (*i) + 1;
	if (dq(2) != 1)
	{
		if (raw_token[var_start] && (raw_token[var_start] == '\''
				|| (!ft_isalpha(raw_token[var_start])
					&& raw_token[var_start] != '_')))
		{
			if (raw_token[var_start] == '\'')
				(*i) += 1;
			else
				(*i) += 2;
			return (0);
		}
	}
	return (1);
}
