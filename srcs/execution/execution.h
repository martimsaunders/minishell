/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:26:14 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/04 13:00:14 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "../minishell.h"

typedef struct s_fds
{
	int		pipe1[2];
	int		pipe2[2];
    int		*current;
	int		*previous;
} t_fds;

typedef struct s_process
{
	t_fds fd;
	pid_t	pid;
	int		processes;
	int		exit_status;
	char	**args;
	char	*path;
}			t_process;

//init
t_process *pc();
void init_fds();
void reset_statics();

//free & close
void	total_exit();
void	free_array(char **array);
void	ft_close(int *fd);
void	close_fds();

//execution process
void	pipex_process(t_command *cmd, char **env);
void	dup_fds(t_command *cmd);
void	process_exit(t_command *cmd);
void	create_pipe();

//exec utils
char **arg_join_front(char **args, char *to_join);
char	*path_validate(char *path, char *cmd);
char	*cmd_path(char *cmd);
int	exit_status_return();

#endif