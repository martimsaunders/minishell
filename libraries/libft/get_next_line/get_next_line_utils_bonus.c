/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:46:27 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 11:46:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_gnl(char *s1)
{
	size_t	i;

	i = 0;
	if (!s1 || !*s1)
		return (0);
	while (s1[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *line)
{
	int	i;

	i = 0;
	if (!line)
	{
		return (NULL);
	}
	while (line[i])
	{
		if (line[i] == '\n')
			return ((char *)line + i);
		i++;
	}
	return (NULL);
}

char	*ft_get_line_gnl(char *temp, char *buffer)
{
	size_t	total;
	size_t	i;
	char	*new_line;

	if (!temp || !*temp)
		return (NULL);
	total = 0;
	while (temp[total] && temp[total] != '\n')
		total++;
	if (temp[total] == '\n')
		total++;
	new_line = malloc(sizeof(char) * total + 1);
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i < total)
		new_line[i] = temp[i];
	new_line[i] = '\0';
	total = 0;
	while (temp[i])
		buffer[total++] = temp[i++];
	buffer[total] = '\0';
	return (new_line);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	total;
	char	*line;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	total = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	line = malloc(sizeof(char) * total + 1);
	if (!line)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			line[i] = s1[i];
			i++;
		}
	}
	total = 0;
	if (s2)
		while (s2[total])
			line[i++] = s2[total++];
	line[i] = '\0';
	return (line);
}
