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
	ft_putstr_fd(cmd->cmd, 2);
	ft_putendl_fd(": command not found", 2);
	close_fds();
	free(pc()->path);
	free_command_list(&pc()->cmd);
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
	dup2(pc()->fd.previous[0], STDIN_FILENO);
}

void open_outfile(t_redirect *outfiles)
{
	t_redirect *file;

	file = outfiles;
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
	dup2(pc()->fd.current[1], STDOUT_FILENO);
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

void	pipex_process(t_command *cmd, char **env)
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
		execve(pc()->path, cmd->args, env);
		process_exit(cmd);
	}
	ft_close(&pc()->fd.previous[0]);
	ft_close(&pc()->fd.current[1]);
}
