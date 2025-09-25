/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:11:12 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/25 11:15:08 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	hd_child_process(t_redirect *file)
{
	char	*line;

	init_signals_here_doc();
	line = NULL;
	while (1)
	{
		line = readline("🧐 > ");
		if (!line || hd_strncmp(line, file->filename,
				ft_strlen(file->filename)) == 0)
		{
			if (!line)
				printf("😵 warning: here-document delimited by end-of-file (wanted `%s')\n",
					file->filename);
			break ;
		}
		if (file->expand == 0)
			line = expand_str(line);
		ft_putendl_fd(line, pc()->fd.hd_fd[1]);
		free(line);
	}
	if (line)
		free(line);
	process_exit();
}

int	here_doc_process(t_redirect *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork() error!"), 1);
	pc()->sigmode = HERE_DOC;
	if (pid == 0)
		hd_child_process(node);
	waitpid(pid, &pc()->exit_status, 0);
	return (exit_status_return());
}

int	write_here_doc(t_command *cmd)
{
	t_redirect	*node;

	node = cmd->infiles;
	while (node)
	{
		if (node->type == 2)
		{
			if (pipe(pc()->fd.hd_fd) < 0)
				return (perror("pipe() error!"), 1);
			pc()->exit_status = here_doc_process(node);
			ft_close(&pc()->fd.hd_fd[1]);
			if (g_sig_detect)
				break ;
		}
		node = node->next;
		if (node && node->type == 2)
			ft_close(&pc()->fd.hd_fd[0]);
	}
	if (!g_sig_detect)
		cmd->hd_fd = dup(pc()->fd.hd_fd[0]);
	ft_close(&pc()->fd.hd_fd[0]);
	return (pc()->exit_status);
}

int	here_docs_check(t_command *cmd)
{
	t_command	*node;

	if (has_here_docs(cmd) == false)
		return (pc()->exit_status);
	node = cmd;
	while (node)
	{
		if (node->has_hd == true)
		{
			pc()->exit_status = write_here_doc(node);
			if (g_sig_detect)
				break ;
		}
		node = node->next;
	}
	return (pc()->exit_status);
}
