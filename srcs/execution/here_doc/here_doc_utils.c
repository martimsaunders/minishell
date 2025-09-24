/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:53:30 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/24 15:09:14 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	has_here_docs(t_command *cmd)
{
	t_command	*node;
	int			hd_count;
	int			*i;

	hd_count = 0;
	node = cmd;
	while (node)
	{
		if (node->has_hd == true)
			hd_count++;
		node = node->next;
	}
	if (!hd_count)
		return (false);
	i = ft_calloc(hd_count + 1, sizeof(int));
	pc()->fd.here_docs = i;
	if (!pc()->fd.here_docs)
		total_exit("malloc() error");
	pc()->fd.here_docs[hd_count] = -1;
	return (true);
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

static char	*fill_new_line(char *begin, char *to_expand, char *end)
{
	char	*line;
	char	*temp;

	if (to_expand)
	{
		line = ft_strjoin(begin, t_env_find_value(to_expand));
		temp = line;
		line = ft_strjoin(temp, end);
		free(temp);
	}
	else
		line = ft_strjoin(begin, end);
	if (begin)
		free(begin);
	if (end)
		free(end);
	return (line);
}

static char	*modify_line(char *line, char *to_expand, int token_size)
{
	char	*begin;
	char	*end;
	int		size;

	size = 0;
	while (line[size] && line[size] != '$')
		size++;
	begin = ft_substr(line, 0, size);
	if (!begin)
		return (free(line), total_exit("malloc error!!"), NULL);
	end = ft_substr(line, token_size + size, ft_strlen(line));
	free(line);
	if (!end)
		return (free(begin), total_exit("malloc error!!"), NULL);
	line = fill_new_line(begin, to_expand, end);
	if (!line)
		total_exit("malloc error!!");
	return (line);
}

char	*expand_str(char *line)
{
	int		size;
	char	*exp;
	char	*token;
	char	*to_expand;

	exp = ft_strchr(line, '$');
	if (!exp)
		return (line);
	size = 0;
	exp++;
	while (exp[size] && ft_isalnum(exp[size]))
		size++;
	if (size == 0)
		return (line);
	token = ft_substr(exp, 0, size);
	if (!token)
		return (free(line), total_exit("malloc error!!"), NULL);
	to_expand = t_env_has_name(token);
	free(token);
	return (modify_line(line, to_expand, size + 1));
}
