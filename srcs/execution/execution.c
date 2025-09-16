/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/16 11:33:23 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execution_process(t_command *cmd, char **env)
{
	if (!pc()->ms_env)
		pc()->ms_env = create_env(env);
	pc()->cmd = cmd;
	pc()->list_size = cmd_lstsize(cmd);
	init_fds();
	if (pc()->list_size > 1)
		pc()->exit_status = pipe_command_process(cmd);
	else if (pc()->list_size == 1)
		pc()->exit_status = single_command_process(cmd);
	close_fds();
	free_command_list(&cmd);
	return (pc()->exit_status);
}

/*
TESTS:
single and multiple exec commands with and without redirects OK 
NOTES:
implementar sinais Ctrl /,D e C
alterar ms_env para linked list
testar exit status para built ins single command
implementar parsing no heredoc.
verificar comportamentos com signals dentro da criação do hd
*/