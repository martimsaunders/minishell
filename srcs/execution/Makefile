# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 12:45:57 by mateferr          #+#    #+#              #
#    Updated: 2025/09/04 11:50:41 by mateferr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = exec

LIB = ../../libraries/libft

OBJ_DIR = obj

SRC = $(wildcard *.c)

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIB) all
	$(CC) $(OBJ) -L$(LIB) -lft -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C $(LIB) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIB) fclean
	rm -f $(NAME)

re: fclean all
