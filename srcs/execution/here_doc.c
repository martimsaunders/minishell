/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:04:58 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/18 16:54:08 by mateferr         ###   ########.fr       */
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

void	hd_child_process(t_redirect *file)
{
	char	*line;

	line = NULL;
	ft_close(&pc()->fd.previous[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || hd_strncmp(line, file->filename,
				ft_strlen(file->filename)) == 0 || signal_detected)
			break ;
		if (file->expand == 0)
			expand_str(line);
		ft_putendl_fd(line, pc()->fd.previous[1]);
		free(line);
	}
	if (line)
		free(line);
	ft_close(&pc()->fd.previous[1]);
	if (signal_detected)
	{
		signal_detected = 0;
		exit(130);
	}
	exit(0);
}

int	create_here_doc(t_redirect *file)
{
	pid_t	pid;

	if (pipe(pc()->fd.previous) < 0)
		return (perror("pipe() error!"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork() error!"), 1);
	if (pid == 0)
		hd_child_process(file);
	ft_close(&pc()->fd.previous[1]);
	waitpid(pid, &pc()->exit_status, 0);
	return (exit_status_return());
}
