/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:53:46 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/05 18:29:33 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	if (ft_strchr(cmd, '/') || getenv("PATH") == NULL)
		return (ft_strdup(cmd));
	path = ft_split(getenv("PATH"), ':');
	if(!path)
		total_exit("malloc() error!");
	i = 0;
	while (!pathname && path[i])
		pathname = path_validate(path[i++], cmd);
	free_array(path);
	if (!pathname)
		return(ft_strdup(cmd));
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

void create_here_doc(char *delimiter) //adicionar expancao e sinal ctrl
{
	size_t limit;
	char *line;
	
	if (pipe(pc()->fd.previous) < 0)
		total_exit("pipe() error!");
	limit = ft_strlen(delimiter);
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		total_exit("mallo() error!");
	while (hd_strncmp(line, delimiter, limit))
	{
		ft_putstr_fd(line, pc()->fd.previous[1]);
		free(line);
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			total_exit("mallo() error!");
	}
	free(line);
	ft_close(&pc()->fd.previous[1]);
}
