/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/15 19:24:19 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	switch_pipe(void)
{
	int	*temp;

	temp = pc()->fd.current;
	pc()->fd.current = pc()->fd.previous;
	pc()->fd.previous = temp;
	if (pipe(pc()->fd.current) < 0)
	{
		perror("pipe() error!");
		return (0);
	}
	return (1);
}

void	process_exit(void)
{
	close(0);
	close(1);
	close_fds();
	if (pc()->path)
		free(pc()->path);
	pc()->path = NULL;
	if (pc()->ms_env)
		free(pc()->ms_env);
	free_command_list(&pc()->cmd);
	exit(pc()->exit_status);
}

void	child_process(t_command *cmd)
{
	if (cmd->infiles)
	{
		if (!open_infile(cmd->infiles))
			total_exit("infile");
	}
	else if (cmd->is_pipe_in)
		dup2(pc()->fd.previous[0], STDIN_FILENO);
	if (cmd->outfiles)
	{
		if (!open_outfile(cmd->outfiles))
			total_exit("outfile");
	}
	else if (cmd->is_pipe_out)
		dup2(pc()->fd.current[1], STDOUT_FILENO);
	close_fds();
	if (is_built_in(cmd))
		process_exit();
	pc()->path = cmd_path(cmd->cmd);
	if (!pc()->path)
		total_exit("malloc() error!!");
	execve(pc()->path, cmd->args, pc()->ms_env);
	perror(cmd->cmd);
	pc()->exit_status = 127;
	process_exit();
}

int clear_forks(void)
{
	while (pc()->processes--)
		wait(NULL);
	perror("fork() error!");
	return (1);	
}

int	pipe_command_process(t_command *cmd)
{
	t_command	*node;

	node = cmd;
	while (node)
	{
		if (!switch_pipe())
			return (1);
		pc()->pid = fork();
		if (pc()->pid == -1)
			return (clear_forks());
		pc()->processes++;
		if (pc()->pid == 0)
			child_process(node);
		ft_close(&pc()->fd.previous[0]);
		ft_close(&pc()->fd.current[1]);
		node = node->next;
	}
	waitpid(pc()->pid, &pc()->exit_status, 0);
	while (--pc()->processes) // verificar, possivel loop a menos ou a mais
		wait(NULL);
	return (exit_status_return());
}
