/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:26:14 by mateferr          #+#    #+#             */
/*   Updated: 2025/09/05 19:02:40 by mateferr         ###   ########.fr       */
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
	char	*path;
	t_command *cmd;
	int list_size;
}			t_process;

//utils
t_process *pc();
int	cmd_lstsize(t_command *lst);

//free exit
void	total_exit(char *msg);
void	free_array(char **array);
void free_command_list(t_command **list);
void free_redirect_list(t_redirect **list);

//fds
void init_fds();
void	ft_close(int *fd);
void	close_fds();
void open_infile(t_redirect *infiles);
void open_outfile(t_redirect *outfiles);

//execution process
void	command_execution(t_command *cmd, char **env);
void	dup_fds(t_command *cmd);
void	process_exit(t_command *cmd, int error);
void	switch_pipe();
void is_built_in(t_command *cmd, char **env);

//exec utils
char	*path_validate(char *path, char *cmd);
char	*cmd_path(char *cmd);
int	exit_status_return();
int	hd_strncmp(const char *s1, const char *s2, size_t n);
void create_here_doc(char *delimiter);

//built ins
void ft_echo(t_command *cmd);
void ft_env(char **env, t_command *cmd);
void ft_pwd(char **env);

#endif