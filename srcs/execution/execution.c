/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:12:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/05 19:10:05 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execution_process(t_command *cmd, char **env)
{
	
	if (!pc()->ms_env)
		pc()->ms_env = create_env(env);
	pc()->cmd = cmd;
	pc()->list_size = cmd_lstsize(cmd);
	init_fds();
	if (pc()->list_size > 1)
		pc()->exit_status = pipe_command_process(cmd);
	else if (pc()->list_size == 1)
		pc()->exit_status = single_command_process(cmd);
	close_fds();
	free_command_list(&cmd);
	return (pc()->exit_status);
}

//test

char **create_arg1(char *cmd)
{
	int n_arg = 1;
	char **arg = ft_calloc(n_arg + 2, sizeof(char *));
	int i = 0;
	arg[i++] = ft_strdup(cmd);
	arg[i++] = ft_strdup("x");
	arg[i] = NULL;
	return arg;
}

char **create_arg2(char *cmd)
{
	int n_arg = 1;
	char **arg = ft_calloc(n_arg + 2, sizeof(char *));
	int i = 0;
	arg[i++] = ft_strdup(cmd);
	arg[i++] = ft_strdup("y");
	arg[i] = NULL;
	return arg;
}

t_redirect *create_files()
{
	t_redirect *node1 = ft_calloc(1, sizeof(t_redirect));
	// t_redirect *node2 = ft_calloc(1, sizeof(t_redirect));
	// t_redirect *node3 = ft_calloc(1, sizeof(t_redirect));
	node1->type = 1;
	node1->filename = ft_strdup("y");
	node1->next = NULL;
	// node2->type = 1;
	// node2->filename = ft_strdup("b");
	// node2->next = node3;
	// node3->type = 1;
	// node3->filename = ft_strdup("a");
	// node3->next = NULL;
	return node1;
}

t_redirect *create_files2()
{
	t_redirect *node1 = ft_calloc(1, sizeof(t_redirect));
	// t_redirect *node2 = ft_calloc(1, sizeof(t_redirect));
	// t_redirect *node3 = ft_calloc(1, sizeof(t_redirect));
	node1->type = 2;
	node1->filename = ft_strdup("x");
	node1->next = NULL;
	// node2->type = 1;
	// node2->filename = ft_strdup("out_2");
	// node2->next = node3;
	// node3->type = 2;
	// node3->filename = ft_strdup("out_3");
	// node3->next = NULL;
	return node1;
}

t_command *fill_list()
{
	t_command *node = ft_calloc(1, sizeof(t_command));
	t_command *node2 = ft_calloc(1, sizeof(t_command));
	node->cmd = ft_strdup("cat");
	node->args = create_arg1(node->cmd);
	node->infiles = NULL;
	node->outfiles = NULL;
	node->next = node2;
	node2->cmd = ft_strdup("cat");
	node2->args = create_arg2(node2->cmd);
	node2->infiles = NULL;
	node2->outfiles = NULL;
	node2->next = NULL;
	return(node);
}

int main(int ac, char **av, char **env) 
{
	int ret = execution_process(fill_list(), env);
	(void)ac;
	(void)av;
	return ret;
}
/*
TESTS:
1 cmd n args 0 rdt => ok valid e invalid commad com 0 ou n args
1 cmd n args n rdtin => ok valid e invalid < e <<
1 cmd n args n rdtin/out => ok valid e invalid > e >>
2 cmd n in n out => ok ok
2 cmd 0 in 0 out => ok ok
NOTES:
implementar sinais Ctrl /,D e C
testar built ins
testar exit status para built ins single command
implementar parsing no heredoc. 
verificar comportamentos com signals dentro da criação do hd
*/