/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:04:58 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/17 17:51:53 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	create_here_doc(char *delimiter)
{
	size_t limit;
	char *line;

	if (pipe(pc()->fd.previous) < 0)
	{
		perror("pipe() error!");
		return ;
	}
	limit = ft_strlen(delimiter);
	printf("> ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		total_exit("mallo() error!");
	while (hd_strncmp(line, delimiter, limit))
	{
		ft_putstr_fd(line, pc()->fd.previous[1]);
		free(line);
		printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			total_exit("mallo() error!");
	}
	free(line);
	ft_close(&pc()->fd.previous[1]);
}
