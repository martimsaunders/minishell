/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:05:14 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 18:26:16 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	single_command_fds_handle(t_command *cmd)
{
	if (cmd->infiles)
		pc()->exit_status = open_infile(cmd);
	if (cmd->outfiles)
		pc()->exit_status = open_outfile(cmd->infiles);
	return (pc()->exit_status);
}

void	single_cmd_child(t_command *cmd)
{
	char	**exec_env;

	init_signals_execve();
	exec_env = NULL;
	close_fds();
	if (!cmd->cmd)
		process_exit();
	pc()->path = cmd_path(cmd->cmd);
	if (!pc()->path)
		total_exit("malloc() error!!");
	create_exec_env(exec_env);
	execve(pc()->path, cmd->args, exec_env);
	free_array(exec_env);
	ft_putstr_fd("😵 ", 2);
	if (!*cmd->cmd)
		ft_putstr_fd("''", 2);
	else
		ft_putstr_fd(cmd->cmd, 2);
	ft_putendl_fd(": command not found", 2);
	pc()->exit_status = 127;
	process_exit();
}

int	single_command_process(t_command *cmd)
{
	pc()->fd.stdin_cpy = dup(STDIN_FILENO);
	pc()->fd.stdout_cpy = dup(STDOUT_FILENO);
	single_command_fds_handle(cmd);
	if (is_built_in(cmd) == 0)
	{
		pc()->pid = fork();
		if (pc()->pid == -1)
		{
			perror("fork() error!");
			return (1);
		}
		pc()->sigmode = EXECVE;
		if (pc()->pid == 0)
			single_cmd_child(cmd);
		waitpid(pc()->pid, &pc()->exit_status, 0);
		if (exit_status_return() == 131)
			ft_putendl_fd("😵 Quit (core dumped)", 2);
	}
	dup2(pc()->fd.stdin_cpy, STDIN_FILENO);
	dup2(pc()->fd.stdout_cpy, STDOUT_FILENO);
	ft_close(&pc()->fd.stdin_cpy);
	ft_close(&pc()->fd.stdout_cpy);;
	return (pc()->exit_status);
}
