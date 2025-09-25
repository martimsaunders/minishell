/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:25:29 by praders           #+#    #+#             */
/*   Updated: 2025/09/25 11:35:33 by mateferr         ###   ########.fr       */
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
