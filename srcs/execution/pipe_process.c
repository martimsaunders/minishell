/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:17:24 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/22 15:55:55 by mateferr         ###   ########.fr       */
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

void redirect_pipe_handle(t_command *cmd)
{
	if (cmd->infiles)
		pc()->exit_status = open_infile(cmd->infiles);
	else if (cmd->is_pipe_in)
		dup2(pc()->fd.previous[0], STDIN_FILENO);
	if (cmd->outfiles)
		pc()->exit_status = open_outfile(cmd->outfiles);
	else if (cmd->is_pipe_out)
		dup2(pc()->fd.current[1], STDOUT_FILENO);
	if (pc()->exit_status == 1)
		total_exit(strerror(errno));
}

void	child_process(t_command *cmd)
{
	char **exec_env;
	
	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
	exec_env = NULL;
	redirect_pipe_handle(cmd);
	close_fds();
	if (!cmd->cmd)
		process_exit();
	if (is_built_in(cmd))
		process_exit();
	pc()->path = cmd_path(cmd->cmd);
	if (!pc()->path)
		total_exit("malloc() error!!");
	create_exec_env(exec_env);
	execve(pc()->path, cmd->args, exec_env);
	free_array(exec_env);
	if (!*cmd->cmd)
		ft_putstr_fd("''", 2);
	else
		ft_putstr_fd(cmd->cmd, 2);
	ft_putendl_fd(": command not found", 2);
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
		pc()->pid_array[pc()->processes] = pc()->pid;
		pc()->processes++;
		if (pc()->pid == 0)
			child_process(node);
		ft_close(&pc()->fd.previous[0]);
		ft_close(&pc()->fd.current[1]);
		node = node->next;
	}
	waitpid(pc()->pid, &pc()->exit_status, 0);
	while (--pc()->processes)
		wait(NULL);
	return (exit_status_return());
}
