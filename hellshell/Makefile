# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile template                                  :+:    :+:             #
#                                                      +:+                     #
#    By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/05/22 15:34:23 by ovan-rhe      #+#    #+#                  #
#    Updated: 2023/06/20 13:26:02 by ovan-rhe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 		= hellshell

SRC_FILES	= main.c

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

####	LIBS 		####
HEADERS		= -I include
# LIB		=
# LIBS		= -L <location> -l<name>

#### 	COMPILING 	####
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
FSAN	= -fsanitize=address


#--RULES------------------------------------------------------------------------

all: tmp $(NAME)

# all: lib tmp $(NAME)

# lib:
# 	@make -C $(LIB)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(HEADERS) $(OBJS) -o $(NAME)

tmp:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(OBJ_DIR) $(NAME)

re: fclean all

.PHONY: all, tmp, clean, fclean, re