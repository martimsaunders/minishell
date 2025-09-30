/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:07:23 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/29 14:23:15 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ms_putstr_fd(char *s1, char *s2, char *s3, int fd)
{
	char	*new_line;
	char	*temp;
	size_t	i;

	if (!s1 && !s2 && !s3)
		return ;
	if (!s2 && !s3)
		new_line = ft_strdup(s1);
	else
	{
		new_line = ft_strjoin(s1, s2);
		if (s3)
		{
			temp = new_line;
			new_line = ft_strjoin(temp, s3);
			free(temp);
		}
	}
	if (!new_line)
		total_exit("malloc error");
	i = ft_strlen(new_line);
	write(fd, new_line, i);
	free(new_line);
}

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
	if (ft_strchr(cmd, '/') || t_env_has_name("PATH") == NULL)
		return (ft_strdup(cmd));
	path = ft_split(t_env_find_value("PATH"), ':');
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

char	**create_exec_env(void)
{
	t_env	*lst;
	int		size;
	int		i;
	char	**exec_env;

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
	return (exec_env);
}
