/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_exp_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:54:31 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/06 10:54:39 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_expansion(char *str, int size)
{
	t_env	*node;

	node = pc()->ms_env;
	while (node)
	{
		if (!ft_strncmp(node->name, str, size) && node->name[size] == '\0')
			break ;
		node = node->next;
	}
	if (!node)
		return (NULL);
	return (node->value);
}

int	digits_manage(char *str, int n)
{
	int	i;
	int	num;

	num = n;
	i = 1;
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	if (str)
	{
		str += (i - 1);
		while (num > 9)
		{
			*str-- = (num % 10) + 48;
			num = num / 10;
		}
		*str = (num % 10) + 48;
	}
	return (i);
}
