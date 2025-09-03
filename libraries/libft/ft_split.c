/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:36:48 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/24 15:58:07 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s1, char const c)
{
	size_t	count;

	count = 0;
	while (*s1)
	{
		while (*s1 == c)
			s1++;
		if (*s1)
		{
			count++;
			while (*s1 != c && *s1)
				s1++;
		}
	}
	return (count);
}

static char	*allocate_string(char const *s1, char const c, size_t *i)
{
	size_t	space;
	char	*newstr;
	size_t	a;

	a = 0;
	space = 0;
	while (s1[*i] == c)
		(*i)++;
	while (s1[*i + space] && s1[*i + space] != c)
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

char	**ft_split(char const *s, char c)
{
	size_t	words;
	size_t	i;
	char	**newstr;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	newstr = malloc(sizeof(char *) * (words + 1));
	if (!newstr)
		return (NULL);
	while (j < words)
	{
		newstr[j] = allocate_string(s, c, &i);
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

/*int	main(void)
{
	char *c = "";
	char set = ' ';
	char **s = ft_split(c, set);
	int a = 0;

	if (!s)
	{
		printf("Erro");
		return (1);
	}
	while (a <= 1)
	{
		printf("Resultado: %s\n", s[a]);
		a++;
	}
	return (0);
}*/