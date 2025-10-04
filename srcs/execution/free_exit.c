/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:04:38 by mateferr          #+#    #+#             */
/*   Updated: 2025/10/01 18:05:56 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	total_exit(char *msg)
{
	perror(msg);
	close_fds();
	if (pc()->path)
		free(pc()->path);
	if (pc()->ms_env)
		delete_t_env_list(&pc()->ms_env);
	if (pc()->cmd)
		free_commands(pc()->cmd);
	clear_history();
	exit(1);
}

void	process_exit(void)
{
	close_fds();
	if (pc()->path)
		free(pc()->path);
	pc()->path = NULL;
	if (pc()->ms_env)
		delete_t_env_list(&pc()->ms_env);
	free_commands(pc()->cmd);
	clear_history();
	exit(pc()->exit_status);
}

void	free_redirect_list(t_redirect **list)
{
	t_redirect	*rdt;
	t_redirect	*node;

	if (!list)
		return ;
	rdt = *list;
	while (rdt)
	{
		node = rdt;
		free(rdt->filename);
		rdt = rdt->next;
		free(node);
	}
	*list = NULL;
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}
