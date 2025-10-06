/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ttk_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:10:30 by praders           #+#    #+#             */
/*   Updated: 2025/10/06 20:28:42 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd_export(char *cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (0);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (0);
	while (cmd[++i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			if (cmd[i] == '+')
			{
				if (cmd[i + 1] != '=')
					return (0);
				else
					return (2);
			}
			else if (cmd[i] == '=')
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

t_command	*handle_world_token(t_command *current_cmd, t_token *current_token)
{
	int	i;

	if (current_cmd->cmd == NULL)
	{
		if ((current_token->is_quoted != 1 && current_token->is_expanded != 1))
		{
			i = check_cmd_export(current_token->value);
			if (i != 0)
			{
				if (!add_redirect(&current_cmd->false_exports,
						current_token->value, current_token->is_quoted, i))
					return (NULL);
				return (current_cmd);
			}
		}
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
	if (type == 2)
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
