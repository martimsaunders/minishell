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
/*
needs expansion
line total size
fill new line
*/

bool needs_expansion(char *str)
{
	str = ft_strchr(str, '$');
	while (str)
	{
		str++;
		if (ft_isalnum(*str) || *str == '_' || *str == '?')
			return (true);
		str = ft_strchr(str, '$');
	}
	return (false);
}

int exit_status_exp(char *str)
{
	int e_status;
	int count;

	count = 0;
	e_status = pc()->exit_status;
	while (e_status >= 10)
	{
		count++;
		e_status = e_status / 10;
	}
	if (str != NULL)
	{
		e_status = pc()->exit_status;
		str += count;
		while (e_status >= 10)
		{
			*str-- = (e_status % 10) + 48;
			e_status = e_status / 10;
		}
	}
	return (count);
}

char *find_expansion(char *str, int size)
{
	t_env	*node;

	if (!*str)
		return (NULL);
	node = pc()->ms_env;
	while (node)
	{
		if (!ft_strncmp(str, node->name, size) && node->name[size] == '\0')
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

int env_exp(char *str, char *dest)
{
	int i;
	char *exp;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	exp = find_expansion(str, i);
	i = 0;
	while (exp && exp[i])
		i++;
	if (dest)
	{
		while (exp && *exp)
			*dest++ = *exp++;
	}
	return (i);
}

int new_line_size(char *str)
{
	int size;

	size = 0;
	while (*str)
	{
		if (*str++ == '$' && (ft_isalnum(*str) || *str == '_' || *str == '?'))
		{
			if (ft_isdigit(*str) || *str == '?')
			{
				if (*str++ == '?')
					size += exit_status_exp(NULL);
			}
			else
			{
				size += env_exp(str, NULL);
				while (ft_isalnum(*str) || *str == '_')
					str++;
			}
		}
		else
			size++;
	}
	return (size);
}

void fill_new_line(char *dest, char *str)
{
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			if (ft_isalnum(*str) || *str == '_' || *str == '?')
			{
				if (ft_isdigit(*str) || *str == '?')
				{
					if (*str == '?')
						dest += exit_status_exp(dest);
					str += 2;
				}
				else
				{
					dest += env_exp(str, dest);
					while (ft_isalnum(*str) || *str == '_')
						str++;
				}
			}
		}
		else
			*dest++ = *str++;
	}
	*dest = '\0';
}

char	*expand_str(char *line)
{
	int new_size;
	char *new_line;

	if (!needs_expansion(line))
		return (line);
	new_size = new_line_size(line);
	new_line = ft_calloc(new_size + 1, sizeof(char));
	if (!new_line)
		return (free(line), total_exit("malloc() error"), NULL);
	fill_new_line(new_line, line);
	free(line);
	return (new_line);
}
//refazer funçao mas bem mais passo a passo