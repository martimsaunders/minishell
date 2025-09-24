/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:05:56 by praders           #+#    #+#             */
/*   Updated: 2025/09/24 14:02:28 by mprazere         ###   ########.fr       */
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
	t_token *current;
	t_token *prev;
	t_token *temp;

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