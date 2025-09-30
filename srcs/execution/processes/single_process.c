/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:09:21 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/29 14:23:16 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	single_command_fds_handle(t_command *cmd)
{
	if (cmd->infiles)
	{
		pc()->exit_status = open_infile(cmd);
		if (pc()->exit_status == 1)
			return (false);
	}
	if (cmd->outfiles)
	{
		pc()->exit_status = open_outfile(cmd->outfiles);
		if (pc()->exit_status == 1)
			return (false);
	}
	return (true);
}

void	exec_fail(char **exec_env, t_command *cmd)
{
	free_array(exec_env);
	if (ft_strchr(cmd->cmd, '/'))
	{
		if (access(cmd->cmd, F_OK) != 0)
		{
			ms_putstr_fd("🤨 ", cmd->cmd, ": No such file or directory\n", 2);
			pc()->exit_status = 127;
		}
		else
		{
			ms_putstr_fd("🥸 ", cmd->cmd, ": Is a directory\n", 2);
			pc()->exit_status = 126;
		}
	}
	else
	{
		if (!*cmd->cmd)
			ms_putstr_fd("😴 ", "''", ": command not found\n", 2);
		else
			ms_putstr_fd("😴 ", cmd->cmd, ": command not found\n", 2);
		pc()->exit_status = 127;
	}
	process_exit();
}

void	single_cmd_child(t_command *cmd)
{
	char	**exec_env;

	init_signals_execve();
	close_fds();
	if (!cmd->cmd)
		process_exit();
	pc()->path = cmd_path(cmd->cmd);
	if (!pc()->path)
		total_exit("malloc() error!!");
	exec_env = create_exec_env();
	execve(pc()->path, cmd->args, exec_env);
	exec_fail(exec_env, cmd);
}

int	single_command_process(t_command *cmd)
{
	pc()->fd.stdin_cpy = dup(STDIN_FILENO);
	pc()->fd.stdout_cpy = dup(STDOUT_FILENO);
	if (single_command_fds_handle(cmd))
	{
		if (is_built_in(cmd) == 0)
		{
			pc()->pid = fork();
			if (pc()->pid == -1)
				return (perror("fork() error!"), 1);
			pc()->sigmode = EXECVE;
			if (pc()->pid == 0)
				single_cmd_child(cmd);
			waitpid(pc()->pid, &pc()->exit_status, 0);
			if (exit_status_return() == 131)
				ft_putendl_fd("😖 Quit (core dumped)", 2);
		}
	}
	dup2(pc()->fd.stdin_cpy, STDIN_FILENO);
	dup2(pc()->fd.stdout_cpy, STDOUT_FILENO);
	return (pc()->exit_status);
}
