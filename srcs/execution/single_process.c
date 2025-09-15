/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:05:14 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/15 18:29:13 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_command *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo", size) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", size) == 0)
		pc()->exit_status = ft_cd(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", size) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->cmd, "export", size) == 0)
		pc()->exit_status = ft_export(cmd);
	else if (ft_strncmp(cmd->cmd, "unset", size) == 0)
		pc()->exit_status = ft_unset(cmd);
	else if (ft_strncmp(cmd->cmd, "env", size) == 0)
		ft_env(cmd);
	else if (ft_strncmp(cmd->cmd, "exit", size) == 0)
		ft_exit();
	else
		return (0);
	return (1);
}

void	single_command_fds_handle(t_command *cmd)
{
	if (cmd->infiles)
		if (!open_infile(cmd->infiles))
			perror("infile");
	if (cmd->outfiles)
		if (!open_outfile(cmd->outfiles))
			perror("outfile");
}

void single_cmd_child(t_command *cmd)
{
	close_fds();
	pc()->path = cmd_path(cmd->cmd);
	if (!pc()->path)
		total_exit("malloc() error!!");
	execve(pc()->path, cmd->args, pc()->ms_env);
	perror(cmd->cmd);
	pc()->exit_status = 127;
	process_exit();
}

int	single_command_process(t_command *cmd)
{
	int backup_stdin;
	int backup_stdout;
	
	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	single_command_fds_handle(cmd);
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
	}
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	close(backup_stdin);
	close(backup_stdout);
	return (exit_status_return()); // verificar se o valor de exit é correto para cada built in
}
