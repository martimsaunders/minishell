/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:10:46 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/25 11:19:55 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	has_here_docs(t_command *cmd)
{
	t_command	*node;
	int			hd_count;

	hd_count = 0;
	node = cmd;
	while (node)
	{
		node->hd_fd = -1;
		if (node->has_hd == true)
			hd_count++;
		node = node->next;
	}
	if (hd_count == 0)
		return (false);
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

static char	*modify_line(char *line, char *to_expand, int token_size,
		bool extit_status)
{
	char	*begin;
	char	*end;
	int		size;

	if (extit_status)
		return (free(line), ft_itoa(pc()->exit_status));
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

	exp = ft_strchr(line, '$');
	if (!exp)
		return (line);
	size = 0;
	exp++;
	while (exp[size] && (ft_isalnum(exp[size]) || exp[size] == '?'))
		size++;
	if (size == 0)
		return (line);
	token = ft_substr(exp, 0, size);
	if (!token)
		return (free(line), total_exit("malloc error!!"), NULL);
	if (size == 1 && ft_strncmp(token, "?", size) == 0)
		line = modify_line(line, NULL, 1, true);
	else
		line = modify_line(line, t_env_has_name(token), size + 1, false);
	free(token);
	if (!line)
		total_exit("malloc() error");
	return (line);
}
