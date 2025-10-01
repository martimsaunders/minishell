/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:36:29 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/01 16:23:14 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_false_exp(t_redirect *vars)
{
	(void)vars;
}

int	is_built_in(t_command *cmd)
{
	if (!cmd->cmd || (!cmd->false_exports && !*cmd->cmd))
		return (0);
	if (cmd->false_exports && !*cmd->cmd)
		ft_false_exp(cmd->false_exports);
	else if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
		pc()->exit_status = ft_echo(cmd->args);
	else if (ft_strncmp(cmd->cmd, "cd", 3) == 0)
		pc()->exit_status = ft_cd(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", 4) == 0)
		pc()->exit_status = ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", 7) == 0)
		ft_export(cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", 6) == 0)
		pc()->exit_status = ft_unset(cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", 4) == 0)
		pc()->exit_status = ft_env(cmd);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ft_exit(cmd->args);
	else
		return (0);
	return (1);
}
