/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/03 18:27:30 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	create_pipe()
{
	int	*temp;
	
	temp = pc()->fd->current;
	pc()->fd->current = pc()->fd->previous;
	pc()->fd->previous = temp;
	if (pipe(pc()->fd->current) == -1)
		total_exit();
}

static void	process_exit(t_command *cmd)
{
	close(0);
	close(1);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putendl_fd(": command not found", 2);
	if (pc()->path)
		free(pc()->path);
	free_array(pc()->args);
	exit(127);
}

void	dup_fds(t_command *cmd)
{
	t_redirect *out;
	
	if (cmd->infile)
		pc()->fd->previous[0] = open(cmd->infile, O_RDONLY);
	if  (cmd->outfiles)
	{
		out = cmd->outfiles;
		while (out)
		{
			if (out->type = 1)
				pc()->fd->current[1] = open(out->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				pc()->fd->current[1] = open(out->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			out = out->next;
		}
	}
	dup2(pc()->fd->previous[0], STDIN_FILENO);
	dup2(pc()->fd->current[1], STDOUT_FILENO);
	close_fds();
}

void	pipex_process(t_command *cmd)
{
	create_pipe();
	pc()->pid = fork();
	pc()->processes++;
	if (pc()->pid == -1)
		total_exit();
	else if (pc()->pid == 0)
	{
		dup_fds(cmd);
		execve(pc()->path, pc()->args, getenv("PATH"));
		process_exit(cmd);
	}
	ft_close(&pc()->fd->previous[0]);
	ft_close(&pc()->fd->current[1]);
}
