/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:28:34 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/06 10:54:46 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	expansion_size_calc(char *str, int *total_size)
{
	char	*start;
	int		adress_move;

	adress_move = 0;
	start = str;
	while (ft_isalnum(*str) || *str == '_')
	{
		adress_move++;
		str++;
	}
	if (total_size)
		*total_size += ft_strlen(find_expansion(start, str - start));
	return (adress_move);
}

int	new_line_total_size(char *str)
{
	int	size;

	size = 0;
	while (*str)
	{
		if (*str++ == '$' && (isalnum(*str) || *str == '_' || *str == '?'))
		{
			if (ft_isdigit(*str) || *str == '?')
			{
				if (*str == '?')
					size += digits_manage(NULL, pc()->exit_status);
				str++;
			}
			else
				str += expansion_size_calc(str, &size);
		}
		else
			size++;
	}
	return (size);
}

int	expansion_new_line_fill(char *str, char *new_line)
{
	char	*start;
	char	*value;
	int		value_size;

	start = str;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	value = find_expansion(start, str - start);
	if (!value)
		return (0);
	value_size = ft_strlen(value);
	ft_memcpy(new_line, value, value_size);
	return (value_size);
}

void	fill_new_line(char *new_line, char *str)
{
	while (*str)
	{
		if (*str == '$' && (ft_isalnum(str[1]) || str[1] == '_'
				|| str[1] == '?'))
		{
			str++;
			if (ft_isdigit(*str) || *str == '?')
			{
				if (*str == '?')
					new_line += digits_manage(new_line, pc()->exit_status);
				str++;
			}
			else
			{
				new_line += expansion_new_line_fill(str, new_line);
				str += expansion_size_calc(str, 0);
			}
		}
		else
			*new_line++ = *str++;
	}
}

char	*expand_str(char *line)
{
	char	*new_line;
	char	*str;
	bool	needs_expansion;

	needs_expansion = false;
	str = ft_strchr(line, '$');
	while (str)
	{
		str++;
		if (ft_isalnum(*str) || *str == '_' || *str == '?')
		{
			needs_expansion = true;
			break ;
		}
		str = ft_strchr(str, '$');
	}
	if (!needs_expansion)
		return (line);
	new_line = ft_calloc(new_line_total_size(line) + 1, sizeof(char));
	if (!new_line)
		return (free(line), total_exit("malloc error"), NULL);
	fill_new_line(new_line, line);
	return (free(line), new_line);
}
