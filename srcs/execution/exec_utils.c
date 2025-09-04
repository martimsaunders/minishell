/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:53:46 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/04 12:52:20 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char **arg_join_front(char **args, char *to_join)
{
	char **new_args;
	int args_memb;
	int i;

	args_memb = 0;
	while(args && args[args_memb] != NULL)
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
	path = ft_split(getenv("PATH"), ':');
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

int	exit_status_return()
{
	if (WIFEXITED(pc()->exit_status))
		return (WEXITSTATUS(pc()->exit_status));
	else if (WIFSIGNALED(pc()->exit_status))
		return (128 + WTERMSIG(pc()->exit_status));
	else
		return (1);
}