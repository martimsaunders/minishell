/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/05 19:09:04 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	switch_pipe()
{
	int	*temp;
	
	temp = pc()->fd.current;
	pc()->fd.current = pc()->fd.previous;
	pc()->fd.previous = temp;
	if (pipe(pc()->fd.current) < 0)
		total_exit("pipe() error!");
}

void	process_exit(t_command *cmd)
{
	close(0);
	close(1);
	close_fds();
	if (pc()->path)
		free(pc()->path);
	pc()->path = NULL;
	if (pc()->ms_env)
		free(pc()->ms_env);
	free_command_list(&pc()->cmd);
	exit(pc()->exit_status);
}

void	dup_fds(t_command *cmd)
{
	if (cmd->infiles)
		open_infile(cmd->infiles);
	else if (pc()->processes != 1)
		dup2(pc()->fd.previous[0], STDIN_FILENO);
	if  (cmd->outfiles)
		open_outfile(cmd->outfiles);
	else if (pc()->processes != pc()->list_size)
		dup2(pc()->fd.current[1], STDOUT_FILENO);
	close_fds();
}

int is_built_in(t_command *cmd)
{
	size_t size;

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

void	command_execution(t_command *cmd)
{
	switch_pipe();
	pc()->pid = fork();
	if (pc()->pid == -1)
	{
		while (pc()->processes--)
			wait(NULL);
		total_exit("fork() error!");
	}
	pc()->processes++;
	if (pc()->pid == 0)
	{
		dup_fds(cmd);
		if (is_built_in(cmd))
			process_exit(cmd);
		pc()->path = cmd_path(cmd->cmd);
		if (!pc()->path)
			total_exit("malloc() error!!");
		execve(pc()->path, cmd->args, pc()->ms_env);
		perror(cmd->cmd);
		pc()->exit_status = 127;
		process_exit(cmd);
	}
	ft_close(&pc()->fd.previous[0]);
	ft_close(&pc()->fd.current[1]);
}
