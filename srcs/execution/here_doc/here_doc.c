/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:04:58 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 14:01:00 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hd_child_process(t_redirect *file, int hd_fd[2])
{
	char	*line;

	init_signals_here_doc();
	pc()->exit_status = 0;
	line = NULL;
	close(hd_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || hd_strncmp(line, file->filename,
				ft_strlen(file->filename)) == 0)
		{
			if (!line)
				printf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n",
					file->filename);
			break ;
		}
		if (file->expand == 0)
			line = expand_str(line);
		ft_putendl_fd(line, hd_fd[1]);
		free(line);
	}
	if (line)
		free(line);
	close(hd_fd[1]);
	process_exit();
}

int	here_doc_process(t_redirect *node, int hd_pipe[2])
{
	pid_t	pid;

	if (pipe(hd_pipe) < 0)
		return (perror("pipe() error!"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork() error!"), 1);
	pc()->sigmode = HERE_DOC;
	if (pid == 0)
		hd_child_process(node, hd_pipe);
	close(hd_pipe[1]);
	waitpid(pid, &pc()->exit_status, 0);
	return (exit_status_return());
}

int	write_here_doc(t_redirect *file, int hd_idx)
{
	int			hd_pipe[2];
	t_redirect	*node;

	node = file;
	while (node)
	{
		if (node->type == 2)
		{
			pc()->exit_status = here_doc_process(node, hd_pipe);
			if (sig_detect)
				break ;
		}
		node = node->next;
		if (node && node->type == 2)
			close(hd_pipe[0]);
	}
	if (!sig_detect)
		pc()->fd.here_docs[hd_idx] = hd_pipe[0];
	return (pc()->exit_status);
}

int	here_docs_check(t_command *cmd)
{
	int			hd_idx;
	t_command	*node;

	if (has_here_docs(cmd) == false)
		return (pc()->exit_status);
	node = cmd;
	hd_idx = 0;
	while (node)
	{
		if (node->has_hd == true)
		{
			pc()->exit_status = write_here_doc(node->infiles, hd_idx);
			if (sig_detect)
				break ;
			node->infiles->hd_fd = pc()->fd.here_docs[hd_idx++];
		}
		node = node->next;
	}
	return (pc()->exit_status);
}
