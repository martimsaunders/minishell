/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:39:56 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/15 16:20:50 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_process	*pc(void)
{
	static t_process	pc;

	return (&pc);
}

int	cmd_lstsize(t_command *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	**create_env(char **env)
{
	char	**ms_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	ms_env = ft_calloc(i + 1, sizeof(char *));
	if (!ms_env)
		total_exit("malloc error!!");
	i = -1;
	while (env[++i])
	{
		ms_env[i] = ft_strdup(env[i]);
		if (!ms_env[i])
			total_exit("malloc error!!");
	}
	ms_env[i] = NULL;
	return (ms_env);
}
