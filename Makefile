# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 16:34:39 by mprazere          #+#    #+#              #
#    Updated: 2025/09/03 10:44:34 by mprazere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_DIR = ./libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a
PHILO_A = libminishell.a

SRCS = srcs/minishell.c 

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs

all: $(LIBFT) $(minishell_A) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MINISHELL_A): $(OBJS)
	@$(AR) $(MINISHELL_A) $(OBJS)
	@echo 'Biblioteca libminishell.a criada!'

$(NAME): $(OBJS) $(MAIN)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(MINISHELL_A) -o $(NAME) -lreadline
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
