/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:57:59 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/29 11:46:34 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	print_commands(t_command *commands)
{
	t_command	*current_cmd;
	int			cmd_count;
	t_redirect	*current_redirect;

	current_cmd = commands;
	cmd_count = 1;
	while (current_cmd)
	{
		printf("=== Comando %d ===\n", cmd_count);
		printf("CMD: %s\n", current_cmd->cmd ? current_cmd->cmd : "(null)");
		// Imprimir args
		printf("ARGS: ");
		if (current_cmd->args)
		{
			for (int i = 0; current_cmd->args[i]; i++)
			{
				printf("[%s] ", current_cmd->args[i]);
			}
		}
		printf("\n");
		// Imprimir infiles (incluindo heredoc)
		printf("INFILES: ");
		current_redirect = current_cmd->infiles;
		if (!current_redirect)
		{
			printf("(null)");
		}
		else
		{
			while (current_redirect)
			{
				if (current_redirect->type == 2)
					printf("[%s (heredoc) expand: %d] ",
						current_redirect->filename, current_redirect->expand);
				else if (current_redirect->type == 1)
					printf("[%s (input)] expand: %d] ",
						current_redirect->filename, current_redirect->expand);
				else
					printf("[%s (unknown) expand: %d] ",
						current_redirect->filename, current_redirect->expand);
				current_redirect = current_redirect->next;
			}
		}
		printf("\n");
		// Imprimir outfiles
		printf("OUTFILES: ");
		current_redirect = current_cmd->outfiles;
		if (!current_redirect)
		{
			printf("(null)");
		}
		else
		{
			while (current_redirect)
			{
				printf("[%s %s expand: %d] ", current_redirect->filename,
					current_redirect->type == 1 ? "(overwrite)" : "(append)",
						current_redirect->expand);
				current_redirect = current_redirect->next;
			}
		}
		printf("\n");
		// Imprimir flags de pipe
		printf("PIPE_IN: %d, PIPE_OUT: %d\n", current_cmd->is_pipe_in,
			current_cmd->is_pipe_out);
		printf("\n");
		current_cmd = current_cmd->next;
		cmd_count++;
	}
}
*/

static int	handle_input(t_parse_state *state)
{
	state->input = readline("😎 minishell: ");
	if (!state->input)
	{
		if (pc()->ms_env)
			delete_t_env_list(&pc()->ms_env);
		return (clear_history(), ft_putendl_fd("😉 exit", STDOUT_FILENO), 0);
	}
	if (state->input[0] == '\0')
		return (free(state->input), 1);
	return (2);
}

static t_command	*process_input(t_parse_state *state)
{
	t_token		*tokens;
	t_command	*cmds;

	tokens = ms_parsing(state);
	if (!tokens)
		return (NULL);
	cmds = tokens_to_commands(tokens);
	if (mv(0) == 1)
		malloc_exit(tokens, state);
	else if (!cmds)
		pc()->exit_status = 2;
	return (free_token_list(tokens, 0), cmds);
}

static void	cleanup(t_parse_state *state)
{
	add_history(state->input);
	free(state->input);
	ft_memset(state, 0, sizeof(t_parse_state));
}

int	main(int argc, char **argv, char **env)
{
	t_parse_state	state;
	int				status;
	t_command		*cmd;

	(void)argv;
	if (argc != 1)
		return (1);
	init_signals();
	ft_memset(&state, 0, sizeof(t_parse_state));
	pc()->ms_env = create_env(env);
	while (1)
	{
		status = handle_input(&state);
		if (status == 0)
			break ;
		else if (status == 2)
		{
			cmd = process_input(&state);
			cleanup(&state);
			if (cmd)
				execution_process(cmd);
		}
	}
	return (0);
}
