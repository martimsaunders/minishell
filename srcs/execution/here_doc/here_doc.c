/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:04:58 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/22 18:08:00 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hd_child_process(t_redirect *file, int hd_fd[2])
{
	char	*line;
	
	pc()->exit_status = 0;
	line = NULL;
	close(hd_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || hd_strncmp(line, file->filename,
				ft_strlen(file->filename)) == 0)
			break ;
		if (file->expand == 0)
			expand_str(line);
		ft_putendl_fd(line, hd_fd[1]);
		free(line);
	}
	if (line)
		free(line);
	close(hd_fd[1]);
	process_exit();
}

int here_doc_process(t_redirect *node, int hd_pipe[2])
{
	pid_t	pid;
	
	if (pipe(hd_pipe) < 0)
		return (perror("pipe() error!"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork() error!"), 1);
	if (pid == 0)
		hd_child_process(node, hd_pipe);
	close(hd_pipe[1]);
	waitpid(pid, &pc()->exit_status, 0);
	return (exit_status_return());
}

int write_here_doc(t_redirect *file, int hd_idx)
{
	int hd_pipe[2];
	t_redirect *node;
	
	node = file;
	while (node)
	{
		if (node->type == 2)
		{
			pc()->exit_status = here_doc_process(node, hd_pipe);
			if (sigint_detected)
				break ;
		}
		node = node->next;
		if (node && node->type == 2)
			close(hd_pipe[0]);
	}
	if (pc()->exit_status == 0)
		pc()->fd.here_docs[hd_idx] = hd_pipe[0];
	return (pc()->exit_status);
}

int	here_docs_check(t_command *cmd)
{
	int hd_idx;
	t_command *node;

	if (has_here_docs(cmd) == false)
		return (pc()->exit_status);
	node = cmd;
	hd_idx = 0;
	while (node)
	{
		if (node->has_hd == true)
		{
			pc()->exit_status = write_here_doc(node->infiles, hd_idx);
			if (pc()->exit_status != 0)
				break ;
			node->infiles->hd_fd = pc()->fd.here_docs[hd_idx++];
		}
		node = node->next;
	}
	return (pc()->exit_status);
}
