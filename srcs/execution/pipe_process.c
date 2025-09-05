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

void	switch_pipe() //need check
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
	ft_putstr_fd(cmd->cmd, 2);
	ft_putendl_fd(": command not found", 2);
	close_fds();
	if (pc()->path)
		free(pc()->path);
	if(cmd)
		free_command_list(&cmd);
	exit(127);
}

void open_infile(t_redirect *infiles)
{
	t_redirect *file;

	file = infiles;
	while(file)
	{
		ft_close(&pc()->fd.previous[0]);
		if (file->type == 1)
			pc()->fd.previous[0] = open(file->filename, O_RDONLY);
		else if (file->type == 2)
			create_here_doc(file->filename);
		if (pc()->fd.previous[0] < 0)
			total_exit(file->filename);
		file = file->next;	
	}
}

void	dup_fds(t_command *cmd)
{
	t_redirect *file;
	
	if (cmd->infiles)
	{
		open_infile(cmd->infiles);
	}
	if  (cmd->outfiles)
	{
		file = cmd->outfiles;
		while (file)
		{
			ft_close(&pc()->fd.current[1]);
			if (file->type == 1)
				pc()->fd.current[1] = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (file->type == 2)
				pc()->fd.current[1] = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (pc()->fd.current[1] < 0)
				total_exit(file->filename);
			file = file->next;
		}
	}
	dup2(pc()->fd.previous[0], STDIN_FILENO);
	dup2(pc()->fd.current[1], STDOUT_FILENO);
	close_fds();
}

void	pipex_process(t_command *cmd, char **env)
{
	switch_pipe();
	pc()->pid = fork();
	pc()->processes++;
	if (pc()->pid == -1)
		total_exit("fork() error!");
	else if (pc()->pid == 0)
	{
		dup_fds(cmd);
		// printf("%s\n", pc()->path);
		// int i = 0;
		// while(pc()->args[i])
		// 	printf("%s\n", pc()->args[i++]);
		execve(pc()->path, cmd->args, env);
		process_exit(cmd);
	}
	ft_close(&pc()->fd.previous[0]);
	ft_close(&pc()->fd.current[1]);
}
