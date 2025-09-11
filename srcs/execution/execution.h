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
#include <errno.h>

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
	char **ms_env;
}			t_process;

//utils
t_process *pc();
int	cmd_lstsize(t_command *lst);
char **create_env(char **env);

//free exit
void	total_exit(char *msg);
void	free_array(char **array);
void free_command_list(t_command **list);
void free_redirect_list(t_redirect **list);

//fds
void init_fds();
void	ft_close(int *fd);
void	close_fds();
int open_infile(t_redirect *infiles);
int open_outfile(t_redirect *outfiles);

//pipe process
void	child_process(t_command *cmd);
void	process_exit(t_command *cmd);
void	switch_pipe();
int is_built_in(t_command *cmd);
int pipe_command_process(t_command *cmd);

//exec utils
char	*path_validate(char *path, char *cmd);
char	*cmd_path(char *cmd);
int	exit_status_return();
int	hd_strncmp(const char *s1, const char *s2, size_t n);
void create_here_doc(char *delimiter);

//single process
int single_command_process(t_command *cmd);
void single_command_fds_handle(t_command *cmd);

//built ins
void ft_echo(t_command *cmd);
void ft_env(t_command *cmd);
void ft_pwd();
void ft_exit();
int ft_cd(t_command *cmd);
int ft_export(t_command *cmd);
int ft_unset(t_command *cmd);

#endif