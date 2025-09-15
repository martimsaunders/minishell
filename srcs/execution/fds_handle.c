/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:37:27 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/05 19:06:38 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void init_fds()
{
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

void	close_fds()
{
	ft_close(&pc()->fd.previous[0]);
	ft_close(&pc()->fd.previous[1]);
	ft_close(&pc()->fd.current[0]);
	ft_close(&pc()->fd.current[1]);
}

int open_infile(t_redirect *infiles)
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
			return (0);
		file = file->next;	
	}
	dup2(pc()->fd.previous[0], STDIN_FILENO);
	return (1);
}

int open_outfile(t_redirect *outfiles)
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
			return (0);
		file = file->next;
	}
	dup2(pc()->fd.current[1], STDOUT_FILENO);
	return (1);
}
