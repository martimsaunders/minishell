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

void	process_exit(t_command *cmd, int error)
{
	close(0);
	close(1);
	if (error)
	{
		ft_putstr_fd(cmd->cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	close_fds();
	if (pc()->path)
		free(pc()->path);
	pc()->path = NULL;
	free_command_list(&pc()->cmd);
	if (error)
		exit(127);
	exit(0);
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

void is_built_in(t_command *cmd, char **env)
{
	size_t size;

	size = ft_strlen(cmd->cmd);
	if (ft_strncmp(cmd->cmd, "echo", size) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", size) == 0)
		ft_cd(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", size) == 0)
		ft_pwd(env);
	else if (ft_strncmp(cmd->cmd, "export", size) == 0)
		ft_export(cmd);
	else if (ft_strncmp(cmd->cmd, "unset", size) == 0)
		ft_unset(cmd);
	else if (ft_strncmp(cmd->cmd, "env", size) == 0)
		ft_env(env, cmd);
	else if (ft_strncmp(cmd->cmd, "exit", size) == 0)
		ft_exit();
	else
		return ;
	process_exit(cmd, 0);
}

void	command_execution(t_command *cmd, char **env)
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
		is_built_in(cmd, env);
		pc()->path = cmd_path(cmd->cmd);
		if (!pc()->path)
			total_exit("malloc() error!!");
		execve(pc()->path, cmd->args, env);
		process_exit(cmd, 1);
	}
	ft_close(&pc()->fd.previous[0]);
	ft_close(&pc()->fd.current[1]);
}
