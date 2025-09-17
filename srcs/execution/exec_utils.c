/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:53:46 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/17 16:24:18 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_validate(char *path, char *cmd)
{
	char	*dirname;
	char	*pathname;

	dirname = ft_strjoin(path, "/");
	if (!dirname)
		total_exit("malloc() error!");
	pathname = ft_strjoin(dirname, cmd);
	free(dirname);
	if (!pathname)
		total_exit("malloc() error!");
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
	if (!cmd)
		return (ft_strdup(""));
	if (ft_strchr(cmd, '/') || getenv("PATH") == NULL)
		return (ft_strdup(cmd));
	path = ft_split(getenv("PATH"), ':');
	if (!path)
		total_exit("malloc() error!");
	i = 0;
	while (!pathname && path[i])
		pathname = path_validate(path[i++], cmd);
	free_array(path);
	if (!pathname)
		return (ft_strdup(cmd));
	return (pathname);
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
		delete_t_env_list(&pc()->ms_env);
	free_command_list(&pc()->cmd);
	exit(pc()->exit_status);
}

int	exec_env_array_fill(char **exec_env, int i)
{
	t_env	*node;
	int		j;
	char	*temp;

	node = pc()->ms_env;
	j = 0;
	while (node && j++ < i)
		node = node->next;
	exec_env[i] = ft_strjoin(node->name, "=");
	if (!exec_env[i])
		return (1);
	temp = exec_env[i];
	exec_env[i] = ft_strjoin(temp, node->value);
	free(temp);
	if (!exec_env[i])
		return (1);
	return (0);
}

void create_exec_env(char **exec_env)
{
	t_env	*lst;
	int		size;
	int		i;

	size = 0;
	lst = pc()->ms_env;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	exec_env = ft_calloc(size + 1, sizeof(char *));
	if (!exec_env)
		total_exit("malloc error!!");
	i = 0;
	while (i < size)
	{
		if (exec_env_array_fill(exec_env, i++) != 0)
		{
			free_array(exec_env);
			total_exit("malloc error!!");
		}
	}
}
