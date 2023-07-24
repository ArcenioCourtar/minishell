# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/28 19:08:38 by ovan-rhe      #+#    #+#                  #
#    Updated: 2023/06/28 19:08:38 by ovan-rhe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#--VARIABLES--------------------------------------------------------------------

NAME 		= hellshell

SRC_FILES	= 	main.c history.c environment.c init.c \
				\
				builtins/builtins.c 		\
				builtins/builtins2.c 		\
				builtins/builtins3.c 		\
				\
				lexer/lexer_main.c 			\
				lexer/token_array_utils.c 	\
				lexer/token_list_utils.c 	\
				\
				parser/cmd_list_utils.c		\
				parser/command_table.c		\
				parser/parser_main.c		\
				parser/redirects.c			\
				\
				testing.c

SRC_DIR		= src
OBJ_DIR		= obj

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

SRCSUBD		= $(shell find $(SRC_DIR) -type d)
OBJSUBD		= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCSUBD))

HEADERS		= -I include

LIBFT		= libft
LIBS		= -L $(LIBFT) -lft -lreadline

CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror $(FSAN)
FSAN	= -fsanitize=address

#--RULES------------------------------------------------------------------------

all: lib objdir $(NAME)

lib:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(FSAN) $(CFLAGS) $(HEADERS) $(LIBS) $(OBJS) -o $(NAME)

objdir:
	@mkdir -p $(OBJSUBD)

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