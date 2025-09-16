/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/16 18:10:48 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_process	*pc(void)
{
	static t_process	pc;

	return (&pc);
}

int	cmd_lstsize(t_command *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

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
finalizar env list e testar
implementar sinais Ctrl /,D e C
alterar ms_env para linked list
testar exit status para built ins single command
implementar parsing no heredoc.
verificar comportamentos com signals dentro da criação do hd
*/