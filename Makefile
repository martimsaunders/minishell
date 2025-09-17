# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 16:34:39 by mprazere          #+#    #+#              #
#    Updated: 2025/09/17 12:59:17 by mateferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
# MINISHELL_A = libminishell.a

SRCS =  srcs/minishell.c \
\
srcs/parsing/ms_parsing.c srcs/parsing/ms_parsing_token_utils.c \
srcs/parsing/ms_parsing_utils.c srcs/parsing/ms_ttk_create_command.c \
srcs/parsing/ms_frees.c srcs/parsing/ms_ttk_tokens.c \
srcs/parsing/ms_ttk_utils.c srcs/parsing/ms_parsing_protok_utils.c \
srcs/parsing/ms_exit_malloc.c srcs/parsing/ms_utils.c \
srcs/parsing/ms_parsing_protok_utils2.c \
\
srcs/execution/built_ins.c srcs/execution/built_ins2.c \
srcs/execution/exec_utils.c srcs/execution/execution.c \
srcs/execution/fds_handle.c srcs/execution/free_exit.c \
srcs/execution/here_doc.c srcs/execution/pipe_process.c \
srcs/execution/single_process.c srcs/execution/env_list.c \
srcs/execution/env_list2.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# AR = ar rcs

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# $(MINISHELL_A): $(OBJS)
#	@$(AR) $(MINISHELL_A) $(OBJS)
#	@echo 'Biblioteca libminishell.a criada!'

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
