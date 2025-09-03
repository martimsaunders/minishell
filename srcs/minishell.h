/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:09:48 by mprazere          #+#    #+#             */
/*   Updated: 2025/09/03 15:15:49 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

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
	char				*filename;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_command
{
	int					is_pipe_in;
	int					heredoc_fd;
	int					is_pipe_out;
	char				*cmd;
	char				**args;
	char				*infile;
	char				*heredoc_delimeter;
	t_redirect			*outfiles;
	struct s_command	*next;
}						t_command;

typedef struct s_token
{
	int					needs_expansion;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_parse_error
{
	int					position;
	char				*message;
}						t_parse_error;

#endif