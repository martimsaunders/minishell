/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:25:29 by praders           #+#    #+#             */
/*   Updated: 2025/09/24 15:02:46 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_exit(t_token *token_list, t_parse_state *state)
{
	free_token_list(token_list);
	free(state->input);
	pc()->exit_status = 1;
	if (pc()->ms_env)
		delete_t_env_list(&pc()->ms_env);
	clear_history();
	exit(1);
}
