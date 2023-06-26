# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/22 15:34:23 by ovan-rhe      #+#    #+#                  #
#    Updated: 2023/06/20 17:35:53 by ovan-rhe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#--VARIABLES--------------------------------------------------------------------

NAME 		= hellshell

SRC_FILES	= main.c history.c

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

HEADERS		= -I include

LIBFT		= libft
LIBS		= -L $(LIBFT) -lft -lreadline

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
FSAN	= -fsanitize=address

#--RULES------------------------------------------------------------------------

all: lib tmp $(NAME)

lib:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) $(OBJS) -o $(NAME)

tmp:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -rf $(OBJ_DIR) $(NAME)
	$(MAKE) -C $(LIBFT) fclean


re: fclean all

.PHONY: all, lib, tmp, clean, fclean, re