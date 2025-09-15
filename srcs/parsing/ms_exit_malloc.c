/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:25:29 by praders           #+#    #+#             */
/*   Updated: 2025/09/15 15:41:08 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_exit(t_token *token_list, t_parse_state *state)
{
	free_token_list(token_list);
	free(state->input);
	pc()->exit_status = 1;
	exit(1);
}