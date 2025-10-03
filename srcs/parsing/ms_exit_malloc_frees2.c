/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_malloc_frees2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:25:29 by praders           #+#    #+#             */
/*   Updated: 2025/10/03 13:26:03 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_exit(t_token *token_list, t_parse_state *state)
{
	free_token_list(token_list, 0);
	free(state->input);
	pc()->exit_status = 1;
	if (pc()->ms_env)
		delete_t_env_list(&pc()->ms_env);
	clear_history();
	exit(1);
}

void	ms_free_split(char **split, int i)
{
	while (split[i])
		free(split[i++]);
	free (split);
}
