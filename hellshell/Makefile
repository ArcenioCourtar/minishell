# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/29 16:00:49 by ovan-rhe      #+#    #+#                  #
#    Updated: 2023/08/29 16:00:49 by ovan-rhe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#--VARIABLES--------------------------------------------------------------------

NAME 		=	hellshell

SRC_FILES	= 	main.c history.c environment.c init.c env_linked_list_func.c\
				\
				builtins/builtin_env_variable_helpers.c \
				builtins/builtin_cd_echo_exit_pwd.c 	\
				builtins/builtin_env_var_assign.c 		\
				builtins/builtin_export_unset.c			\
				\
				lexer/lexer_main.c 				\
				lexer/token_array_utils.c 		\
				lexer/token_list_functions.c	\
				lexer/token_list_node_utils.c	\
				\
				parser/cmd_lst/cmd_list_functions.c		\
				parser/cmd_lst/cmd_list_node_utils.c	\
				parser/cmd_lst/cmd_list_node.c			\
				parser/cmd_lst/command_table.c			\
				parser/expansion/exp_quotes.c		\
				parser/expansion/exp_quotes_utils.c	\
				parser/expansion/exp_main.c			\
				parser/free_list_functions.c	\
				parser/parser_error.c		\
				parser/parser_main.c		\
				parser/quotes.c				\
				\
				executor/cmd_list_final.c	\
				executor/executor_main.c	\
				executor/exec_cleanup.c		\
				executor/exec_prep.c		\
				executor/forked_process.c	\
				\
				err_handling/ft_fd_printf_utils.c \
				err_handling/ft_fd_printf.c \
				\
				signals.c					\
				\
				testing.c

SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= include
RDL_DIR = $(shell brew --prefix readline)

OBJS	= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
DEP_FILES	= $(OBJS:.o=.d)

SRCSUBD	= $(shell find $(SRC_DIR) -type d)
OBJSUBD	= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCSUBD))

LIBFT	= libft
LIBS	= -L./$(LIBFT) -lft -L$(RDL_DIR)/lib -lreadline

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP

#--RULES------------------------------------------------------------------------

all: lib objdir $(NAME)

lib:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

objdir:
	@mkdir -p $(OBJSUBD)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(RDL_DIR)/include -o $@ -c $<

-include $(DEP_FILES)

clean:
	@rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -rf $(OBJ_DIR) $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

fsan: CFLAGS += -fsanitize=address
debug: CFLAGS += -g
asan tsan debug: re

.PHONY: all lib tmp clean fclean re fsan debug

valg: all
	valgrind --suppressions=../valgrind_suppr.log --leak-check=full ./hellshell