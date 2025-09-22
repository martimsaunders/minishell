/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:09:48 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/22 18:04:33 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define WORD_TOKEN 0
# define PIPE_TOKEN 1
# define REDIRECT_IN_TOKEN 2
# define REDIRECT_OUT_TOKEN 3
# define HEREDOC_TOKEN 4
# define APPEND_TOKEN 5

# define ERRQUO "😵 minishell: syntax error: unexpected end of file\n"
# define PARERR "😵 minishell: syntax error near unexpected token"

extern int				sigint_detected;

typedef struct s_parse_state
{
	int					current;
	int					in_quotes;
	int					token_start;
	char				*input;
	char				quote_char;
}						t_parse_state;

typedef struct s_redirect
{
	int					type;
	bool				expand;
	int					hd_fd;
	char				*filename;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_command
{
	int					is_pipe_in;
	int					is_pipe_out;
	bool				has_hd;
	char				*cmd;
	char				**args;
	t_redirect			*infiles;
	t_redirect			*outfiles;
	struct s_command	*next;
}						t_command;

typedef struct s_token
{
	int					type;
	int					index;
	int					is_quoted;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_parse_error
{
	int					position;
	char				*message;
}						t_parse_error;

// execution structs

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_fds
{
	int					*here_docs;
	int					pipe1[2];
	int					pipe2[2];
	int					*current;
	int					*previous;
}						t_fds;

typedef struct s_process
{
	t_fds				fd;
	pid_t				pid;
	pid_t				*pid_array;
	int					processes;
	int					exit_status;
	char				*path;
	t_command			*cmd;
	int					list_size;
	t_env				*ms_env;
}						t_process;

int						mv(int set_value);
int						dq(int set_value);
int						hd(int set_value);
int						is_quote(char c);
int						is_op(char c);
int						handle_dollar_count3(char *raw_token, int *i,
							int var_start);
int						handle_dollar_alloc3(char *raw_token, int *i,
							int var_start);
int						add_redirect(t_redirect **head, char *filename,
							int is_quoted, int is_append);
int						handle_dollar_count(char *raw_token, int *i, int *size);
int						process_loop(char *raw_token, char *token, int *size,
							int i);
int						process_operator2(t_parse_state *state, int add,
							t_token **new_token);
int						ttc_redirects_in(t_command *current_cmd,
							t_token **current_token, int type);
int						ttc_redirects_out(t_command *current_cmd,
							t_token **current_token, int type);
int						handle_dollar_alloc(char *token, char *raw_token,
							int *i, int *size);
char					**build_args_array(t_token *start);
char					*extract_token(t_parse_state *state, int start,
							int finish, int *is_quoted);
void					free_args(char **args, int i);
void					free_token_list(t_token *head);
void					free_command(t_command *command);
void					free_commands(t_command *commands);
void					free_redirects(t_redirect *redirects);
void					remove_empty_tokens(t_token **token_list);
void					add_token_list(t_token **head, t_token *new_token);
void					malloc_exit(t_token *token_list, t_parse_state *state);
t_token					*create_token(char *value, int type, int is_quoted);
t_token					*ms_parsing(t_parse_state *state);
t_command				*create_command(void);
t_command				*tokens_to_commands(t_token *tokens);
t_command				*ttc_pipe_token(t_command *current_cmd,
							t_token *current_token);
t_command				*handle_world_token(t_command *current_cmd,
							t_token *current_token);

// execution functions
void					init_signals();
int						execution_process(t_command *cmd, char **env);
t_process				*pc(void);
int						cmd_lstsize(t_command *lst);

// t_env list
t_env					*create_env(char **env);
void					t_env_add_back(t_env **list, t_env *node);
void					value_fill(t_env *node, char *str);
void					name_fill(t_env *node, char *str);
void					delete_t_env_list(t_env **list);
t_env					*create_env_node(char *str);
int						update_env(char *name, char *value);
void					remove_env(char *name);
char					*t_env_find_value(char *name);
char					*t_env_has_name(char *str);

// free exit
void					total_exit(char *msg);
void					free_array(char **array);
void					free_command_list(t_command **list);
void					free_redirect_list(t_redirect **list);

// fds
void					init_fds(void);
void					ft_close(int *fd);
void					close_fds(void);
int						open_infile(t_redirect *infiles);
int						open_outfile(t_redirect *outfiles);

// pipe process
void					child_process(t_command *cmd);
int						switch_pipe(void);
int						pipe_command_process(t_command *cmd);
int						clear_forks(void);
void					redirect_pipe_handle(t_command *cmd);

// exec utils
char					*path_validate(char *path, char *cmd);
char					*cmd_path(char *cmd);
int						exit_status_return(void);
void					process_exit(void);
void					create_exec_env(char **exec_env);

// here doc
int						here_docs_check(t_command *cmd);
void					expand_str(char *line);
int						hd_strncmp(const char *s1, const char *s2, size_t n);
void					hd_child_process(t_redirect *file, int hd_fd[2]);
bool has_here_docs(t_command *cmd);

// single process
int						single_command_process(t_command *cmd);
int						single_command_fds_handle(t_command *cmd);
void					single_cmd_child(t_command *cmd);
int						is_built_in(t_command *cmd);

// built ins
int						ft_echo(t_command *cmd);
int						ft_env(t_command *cmd);
void					ft_exit(void);
int						ft_pwd(void);
int						ft_cd(t_command *cmd);
int						ft_export(char **args);
int						ft_unset(char **args);

#endif