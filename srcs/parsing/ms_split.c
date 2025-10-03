/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:15:32 by praders           #+#    #+#             */
/*   Updated: 2025/10/03 14:42:19 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char *s1)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (s1[i])
	{
		while (is_ws(s1, i))
			i++;
		if (s1)
		{
			count++;
			while (s1[i] && !is_ws(s1, i))
				i++;
		}
	}
	return (count);
}

static char	*allocate_string(char *s1, size_t *i)
{
	size_t	space;
	char	*newstr;
	size_t	a;

	a = 0;
	space = 0;
	while (is_ws(s1, *i))
		(*i)++;
	while (s1[*i + space] && !is_ws(s1, *i + space))
		space++;
	newstr = malloc(sizeof(char) * (space + 1));
	if (!newstr)
		return (NULL);
	while (space--)
		newstr[a++] = s1[(*i)++];
	newstr[a] = '\0';
	return (newstr);
}

static void	free_split(char **newstr, size_t j)
{
	while (j > 0)
		free(newstr[--j]);
	free(newstr);
}

static char	**ft_split_ws(char *s)
{
	size_t	words;
	size_t	i;
	char	**newstr;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = count_words(s);
	newstr = malloc(sizeof(char *) * (words + 1));
	if (!newstr)
		return (NULL);
	while (j < words)
	{
		newstr[j] = allocate_string(s, &i);
		if (!newstr[j])
		{
			free_split(newstr, j);
			return (NULL);
		}
		j++;
	}
	newstr[j] = NULL;
	return (newstr);
}

char	**split_token_ws(char *value, int *error, int is_quoted)
{
	int		has_ws;
	int		i;
	char	**split;

	i = -1;
	has_ws = 0;
	if (is_quoted)
		return (NULL);
	while (value[++i])
	{
		if (is_ws(value, i))
		{
			has_ws = 1;
			break ;
		}
	}
	if (has_ws)
	{
		split = ft_split_ws(value);
		if (!split)
			return (*error = 1, NULL);
		return (split);
	}
	return (NULL);
}
