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

#include "../minishell.h"

int	hd_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n)
		i++;
	if (s1[i] == '\n' && i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

bool has_here_docs(t_command *cmd)
{
	t_command *node;
	int hd_count;

	hd_count = 0;
	node = cmd;
	while(node)
	{
		if (node->has_hd == true)
			hd_count++;
		node = node->next;
	}
	if (!hd_count)
		return (false);
	pc()->fd.here_docs = ft_calloc(hd_count + 1, sizeof(int));
	if (!pc()->fd.here_docs)
		total_exit("malloc() error");
	pc()->fd.here_docs[hd_count] = -1;
	return (true);
}

int write_here_doc(t_redirect *file, int hd_idx)
{
	pid_t	pid;
	int hd_pipe[2];
	t_redirect *node;
	
	node = file;
	while (node)
	{
		if (node->type == 2)
		{
			if (pipe(hd_pipe) < 0)
				return (perror("pipe() error!"), 1);
			pid = fork();
			if (pid == -1)
				return (perror("fork() error!"), 1);
			if (pid == 0)
				hd_child_process(node, hd_pipe);
			close(hd_pipe[1]);
			waitpid(pid, &pc()->exit_status, 0);
			if (sigint_detected)
				break ;
		}
		node = node->next;
		if (node && node->type == 2)
			close(hd_pipe[0]);
	}
	if (exit_status_return() == 0)
		pc()->fd.here_docs[hd_idx] = hd_pipe[0];
	return (pc()->exit_status);
}

int	create_here_doc(t_command *cmd)
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
