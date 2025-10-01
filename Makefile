# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 16:34:39 by mprazere          #+#    #+#              #
#    Updated: 2025/10/01 16:16:42 by mateferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  srcs/minishell.c \
\
srcs/parsing/ms_parsing.c srcs/parsing/ms_parsing_token_utils.c \
srcs/parsing/ms_parsing_utils.c srcs/parsing/ms_ttk_create_command.c \
srcs/parsing/ms_frees.c srcs/parsing/ms_ttk_tokens.c \
srcs/parsing/ms_ttk_utils.c srcs/parsing/ms_parsing_protok_utils.c \
srcs/parsing/ms_exit_malloc.c srcs/parsing/ms_utils.c \
srcs/parsing/ms_parsing_protok_utils2.c \
\
srcs/execution/built_ins/built_ins.c srcs/execution/built_ins/built_ins2.c \
srcs/execution/processes/execve_utils.c srcs/execution/execution.c \
srcs/execution/fds_handle.c srcs/execution/free_exit.c \
srcs/execution/here_doc/here_doc.c srcs/execution/processes/pipe_process.c \
srcs/execution/processes/single_process.c srcs/execution/lists/list_manage.c \
srcs/execution/lists/create_list.c srcs/execution/here_doc/here_doc_utils.c \
srcs/execution/signals.c srcs/execution/built_ins/built_ins_utils.c \
srcs/execution/here_doc/here_doc_exp.c srcs/execution/built_ins/ft_export.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo 'minishell compilado!'

clean:
	@rm -f $(OBJS)
	@rm -f $(MINISHELL_A)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo 'Objetos limpos!'

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo 'Tudo limpo!'

re: fclean all

.PHONY: all clean fclean re
