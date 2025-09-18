/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:53:30 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/18 16:54:41 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*fill_new_line(char *begin, char *to_expand, char *end)
{
	char	*line;
	char	*temp;

	if (to_expand)
	{
		line = ft_strjoin(begin, t_env_find_value(to_expand));
		temp = line;
		line = ft_strjoin(temp, end);
	}
	else
		line = ft_strjoin(begin, end);
	return (line);
}

static void	modify_line(char *line, char *to_expand, int token_size)
{
	char	*begin;
	char	*end;
	int		size;

	size = 0;
	while (line[size] && line[size] != '$')
		size++;
	begin = ft_substr(line, 0, size);
	if (!begin)
		return (free(line), total_exit("malloc error!!"));
	end = ft_substr(line, token_size + size, ft_strlen(line));
	free(line);
	if (!end)
		return (free(begin), total_exit("malloc error!!"));
	line = fill_new_line(begin, to_expand, end);
	free(begin);
	free(end);
	if (!line)
		total_exit("malloc error!!");
}

void	expand_str(char *line)
{
	int		size;
	char	*exp;
	char	*token;
	char	*to_expand;

	exp = ft_strchr(line, '$');
	if (!exp)
		return ;
	size = 0;
	exp++;
	while (exp[size] && ft_isalnum(exp[size]))
		size++;
	if (size == 0)
		return ;
	token = ft_substr(exp, 0, size);
	if (!token)
		return (free(line), total_exit("malloc error!!"));
	to_expand = t_env_has_name(token);
	free(token);
	modify_line(line, to_expand, size + 1);
}
