/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/15 16:20:27 by mateferr         ###   ########.fr       */
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
1 cmd n args 0 rdt => ok valid e invalid commad com 0 ou n args
1 cmd n args n rdtin => ok valid e invalid < e <<
1 cmd n args n rdtin/out => ok valid e invalid > e >>
2 cmd n in n out => ok ok
2 cmd 0 in 0 out => ok ok
NOTES:
implementar sinais Ctrl /,D e C
testar built ins
testar exit status para built ins single command
implementar parsing no heredoc.
verificar comportamentos com signals dentro da criação do hd
*/