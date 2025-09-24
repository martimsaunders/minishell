/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:37:27 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 18:46:05 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_fds(void)
{
	pc()->fd.stdin_cpy = -1;
	pc()->fd.stdout_cpy = -1;
	pc()->fd.hd_fd[0] = -1;
	pc()->fd.hd_fd[1] = -1;
	pc()->fd.pipe1[0] = -1;
	pc()->fd.pipe1[1] = -1;
	pc()->fd.pipe2[0] = -1;
	pc()->fd.pipe2[1] = -1;
	pc()->fd.current = pc()->fd.pipe2;
	pc()->fd.previous = pc()->fd.pipe1;
}

void	ft_close(int *fd)
{
	if (*fd >= 0)
		close(*fd);
	*fd = -1;
}

void	close_fds(void)
{
	t_command *node;

	node = pc()->cmd;
	while (node)
	{
		ft_close(&node->hd_fd);
		node = node->next;
	}
	ft_close(&pc()->fd.previous[0]);
	ft_close(&pc()->fd.previous[1]);
	ft_close(&pc()->fd.current[0]);
	ft_close(&pc()->fd.current[1]);
	ft_close(&pc()->fd.hd_fd[0]);
	ft_close(&pc()->fd.hd_fd[1]);
	ft_close(&pc()->fd.stdin_cpy);
	ft_close(&pc()->fd.stdout_cpy);
}

int	open_infile(t_command *cmd)
{
	t_redirect	*file;
	int fd;

	file = cmd->infiles;
	pc()->exit_status = 0;
	while (file)
	{
		ft_close(&pc()->fd.previous[0]);
		if (file->type == 1)
		{
			fd = open(file->filename, O_RDONLY);
			pc()->fd.previous[0] = fd;
			if (pc()->fd.previous[0] < 0)
				return (ft_putstr_fd("😵 minishell: ", 2), perror(file->filename), 1);
		}
		else if (file->type == 2)
			pc()->fd.previous[0] = dup(cmd->hd_fd);
		file = file->next;
	}
	dup2(pc()->fd.previous[0], STDIN_FILENO);
	ft_close(&cmd->hd_fd);
	return (pc()->exit_status);
}

int	open_outfile(t_redirect *outfiles)
{
	t_redirect	*file;
	int fd;

	file = outfiles;
	while (file)
	{
		if (file->type == 1)
			fd = open(file->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == 2)
			fd = open(file->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		pc()->fd.current[1] = fd;
		if (pc()->fd.current[1] < 0)
			return (ft_putstr_fd("😵 minishell: ", 2), perror(file->filename), 1);
		file = file->next;
	}
	dup2(pc()->fd.current[1], STDOUT_FILENO);
	return (0);
}
