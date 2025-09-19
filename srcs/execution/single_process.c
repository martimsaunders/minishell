/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:05:14 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/18 12:30:07 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_command *cmd) //check exit status
{
	size_t	size;

	if (!cmd->cmd || !*cmd->cmd)
		return (0);
	size = ft_strlen(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo", size) == 0)
		pc()->exit_status = ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", size) == 0)
		pc()->exit_status = ft_cd(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", size) == 0)
		pc()->exit_status = ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", size) == 0)
		pc()->exit_status = ft_export(cmd->args);
	else if (ft_strncmp(cmd->cmd, "unset", size) == 0)
		pc()->exit_status = ft_unset(cmd->args);
	else if (ft_strncmp(cmd->cmd, "env", size) == 0)
		pc()->exit_status = ft_env(cmd);
	else if (ft_strncmp(cmd->cmd, "exit", size) == 0)
		ft_exit();
	else
		return (0);
	return (1);
}

int	single_command_fds_handle(t_command *cmd)
{
	if (cmd->infiles)
		pc()->exit_status = open_infile(cmd->infiles);
	if (cmd->outfiles)
		pc()->exit_status = open_outfile(cmd->outfiles);
	return (pc()->exit_status);
}

void single_cmd_child(t_command *cmd)
{
	char **exec_env;
	
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
	if (!*cmd->cmd)
		ft_putstr_fd("''", 2);
	else
		ft_putstr_fd(cmd->cmd, 2);
	ft_putendl_fd(": command not found", 2);;
	pc()->exit_status = 127;
	process_exit();
}

void restore_fds(int backup_stdin, int backup_stdout)
{
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	close(backup_stdin);
	close(backup_stdout);
}

int	single_command_process(t_command *cmd)
{
	int backup_stdin;
	int backup_stdout;
	
	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	if (single_command_fds_handle(cmd) == 0)
	{
		if (is_built_in(cmd) == 0)
		{
			pc()->pid = fork();
			if (pc()->pid == -1)
			{
				perror("fork() error!");
				return (1);
			}
			if (pc()->pid == 0)
				single_cmd_child(cmd);
			waitpid(pc()->pid, &pc()->exit_status, 0);
			pc()->exit_status = exit_status_return();
		}
	}
	restore_fds(backup_stdin, backup_stdout);
	return (pc()->exit_status);
}
