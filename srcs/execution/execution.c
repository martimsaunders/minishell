/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/17 17:54:01 by mateferr         ###   ########.fr       */
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

int	exit_status_return(void)
{
	if (WIFEXITED(pc()->exit_status))
		return (WEXITSTATUS(pc()->exit_status));
	else if (WIFSIGNALED(pc()->exit_status))
		return (128 + WTERMSIG(pc()->exit_status));
	else
		return (1);
}

int	execution_process(t_command *cmd, char **env)
{
	if (!pc()->ms_env)
		pc()->ms_env = create_env(env);
	pc()->cmd = cmd;
	pc()->list_size = cmd_lstsize(cmd);
	init_fds();
	if (pc()->list_size > 1)
	{
		pc()->pid_array = ft_calloc(pc()->list_size + 1, sizeof(pid_t));
		if (!pc()->pid_array)
			total_exit("malloc error!!");
		pc()->pid_array[pc()->list_size] = -1;
		pc()->exit_status = pipe_command_process(cmd);
	}
	else if (pc()->list_size == 1)
		pc()->exit_status = single_command_process(cmd);
	close_fds();
	free_command_list(&cmd);
	return (pc()->exit_status);
}

/*
TESTS:
single and multiple exec commands with and without redirects OK 
built ins simple commands OK
NOTES:
here doc deve ser a primeira coisa a se fazer e nao roda nenhum processo em simultaneo
erro em kill processes
*/