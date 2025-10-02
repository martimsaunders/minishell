/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:28:34 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/02 12:34:19 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static bool	line_first_number(char *exp, char **line)
{
	char	*temp;

	if (ft_isdigit(*exp))
	{
		exp++;
		temp = *line;
		*line = ft_strdup(exp);
		free(temp);
		if (!line)
			total_exit("malloc() error");
		return (true);
	}
	return (false);
}

char	*token_expansion(char *line, char *exp, int size)
{
	char	*token;
	char	*new_line;

	token = ft_substr(exp, 0, size);
	if (!token)
		return (free(line), total_exit("malloc error!!"), NULL);
	if (size == 1 && ft_strncmp(token, "?", size) == 0)
		new_line = modify_line(line, NULL, 1, true);
	else
		new_line = modify_line(line, t_env_has_name(token), size + 1, false);
	free(token);
	if (!new_line)
		total_exit("malloc() error");
	return (new_line);
}

char	*expand_str(char *line)
{
	int		size;
	char	*exp;

	exp = ft_strchr(line, '$');
	if (!exp)
		return (line);
	size = 0;
	exp++;
	if (line_first_number(exp, &line))
		return (line);
	while (exp[size] && (ft_isalnum(exp[size]) || exp[size] == '?'
			|| exp[size] == '_'))
		size++;
	if (size == 0)
		return (line);
	line = token_expansion(line, exp, size);
	return (line);
}
