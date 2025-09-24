/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ttk_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:10:30 by praders           #+#    #+#             */
/*   Updated: 2025/09/24 14:02:25 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*handle_world_token(t_command *current_cmd, t_token *current_token)
{
	if (current_cmd->cmd == NULL)
	{
		current_cmd->cmd = ft_strdup(current_token->value);
		if (!current_cmd->cmd)
			return (mv(1), NULL);
		current_cmd->args = build_args_array(current_token);
		if (!current_cmd->args)
			return (free(current_cmd->cmd), NULL);
	}
	return (current_cmd);
}

t_command	*ttc_pipe_token(t_command *current_cmd, t_token *current_token)
{
	t_command	*new_cmd;

	if (current_token->index == 0)
	{
		if (!current_token->next || current_token->next->type != PIPE_TOKEN)
			return (ft_putstr_fd(PARERR " `|'\n", 2), NULL);
		else if (current_token->next->type == PIPE_TOKEN)
			return (ft_putstr_fd(PARERR " `||'\n", 2), NULL);
	}
	else if (!current_token->next)
		return (ft_putstr_fd(PARERR " `|'\n", 2), NULL);
	else if (current_token->next->type == PIPE_TOKEN)
		return (ft_putstr_fd(PARERR " `||'\n", 2), NULL);
	new_cmd = create_command();
	if (!new_cmd)
		return (NULL);
	current_cmd->is_pipe_out = 1;
	current_cmd->next = new_cmd;
	current_cmd = new_cmd;
	current_cmd->is_pipe_in = 1;
	return (current_cmd);
}

int	ttc_redirects_in(t_command *current_cmd, t_token **current_token, int type)
{
	*current_token = (*current_token)->next;
	if (!*current_token)
		return (ft_putstr_fd(PARERR " `newline'\n", 2), 0);
	else if ((*current_token)->type == PIPE_TOKEN)
		return (ft_putstr_fd(PARERR " `|'\n", 2), 0);
	else if ((*current_token)->type == REDIRECT_IN_TOKEN)
		return (ft_putstr_fd(PARERR " `<'\n", 2), 0);
	else if ((*current_token)->type == HEREDOC_TOKEN)
		return (ft_putstr_fd(PARERR " `<<'\n", 2), 0);
	else if ((*current_token)->type == REDIRECT_OUT_TOKEN)
		return (ft_putstr_fd(PARERR " `>'\n", 2), 0);
	else if ((*current_token)->type == APPEND_TOKEN)
		return (ft_putstr_fd(PARERR " `>>'\n", 2), 0);
	current_cmd->has_hd = true;
	if (!add_redirect(&current_cmd->infiles, (*current_token)->value,
			(*current_token)->is_quoted, type))
		return (0);
	return (1);
}

int	ttc_redirects_out(t_command *current_cmd, t_token **current_token, int type)
{
	*current_token = (*current_token)->next;
	if (!*current_token)
		return (ft_putstr_fd(PARERR " `newline'\n", 2), 0);
	else if ((*current_token)->type == PIPE_TOKEN)
		return (ft_putstr_fd(PARERR " `|'\n", 2), 0);
	else if ((*current_token)->type == REDIRECT_OUT_TOKEN)
		return (ft_putstr_fd(PARERR " `>'\n", 2), 0);
	else if ((*current_token)->type == APPEND_TOKEN)
		return (ft_putstr_fd(PARERR " `>>'\n", 2), 0);
	else if ((*current_token)->type == REDIRECT_IN_TOKEN)
		return (ft_putstr_fd(PARERR " `<'\n", 2), 0);
	else if ((*current_token)->type == HEREDOC_TOKEN)
		return (ft_putstr_fd(PARERR " `<<'\n", 2), 0);
	if (!add_redirect(&current_cmd->outfiles, (*current_token)->value,
			(*current_token)->is_quoted, type))
		return (0);
	return (1);
}
