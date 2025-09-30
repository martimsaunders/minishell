/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:35:59 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/30 16:36:02 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
