/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/03 18:31:05 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char **arg_join_front(char **args, char *to_join)
{
	char **new_args;
	int args_memb;
	int i;

	args_memb = 0;
	while(args[args_memb] != NULL)
		args_memb++;
	new_args = ft_calloc(args_memb + 2, sizeof(char *));
	if (!new_args)
		total_exit();
	new_args[0] = ft_strdup(to_join);
	if (!new_args[0])
		total_exit();
	i = 0;
	while (++i <= args_memb)
	{
		new_args[i] = args[i];
		if(!new_args[i])
			total_exit();
	}
	new_args[i] = NULL;
	return (new_args);
}

char	*path_validate(char *path, char *cmd)
{
	char	*dirname;
	char	*pathname;

	dirname = ft_strjoin(path, "/");
	if (!dirname)
		total_exit();
	pathname = ft_strjoin(dirname, cmd);
	free(dirname);
	if (!pathname)
		total_exit();
	if (!access(pathname, X_OK))
		return (pathname);
	free(pathname);
	return (NULL);
}

char	*cmd_path(char *cmd)
{
	int		i;
	char	**path;
	char	*pathname;

	pathname = NULL;
	path = NULL;
	if (ft_strchr(cmd, '/') || getenv("PATH") == NULL)
		return(cmd);
	path = ft_split(getenv("PATH"), ":");
	if(!path)
		total_exit();
	i = 0;
	while (!pathname && path[i])
		pathname = path_validate(path[i++], cmd);
	free_array(path);
	if (!pathname)
		return(cmd);
	return (pathname);
}

int	execve_process(t_command *cmd)
{
	t_command *node;
	
	node = cmd;
	pc()->fd->current = pc()->fd->pipe1;
	pc()->fd->previous = pc()->fd->pipe2;
	while (node)
	{
		pc()->args = arg_join_front(cmd->args, cmd->cmd);
		pc()->path = cmd_path(cmd->cmd);
		pipex_process();
		free(pc()->path);
		free_array(pc()->args);
		node = node->next;
	}
	waitpid(pc()->pid, &pc()->exit_status, 0);
	pc()->processes--;
	while (pc()->processes--)
		wait(NULL);	
	return (0);//exit status last process reset structs
}
