# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/06 13:32:03 by ovan-rhe      #+#    #+#                  #
#    Updated: 2023/05/08 16:58:24 by ovan-rhe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#--VARIABLES--------------------------------------------------------------------

NAME = libft.a

SRC_FILES =	alloc_free/free_double_array.c	alloc_free/ft_calloc.c 				\
			\
			char_check/ft_isalnum.c	char_check/ft_isalpha.c						\
			char_check/ft_isascii.c	char_check/ft_isdigit.c						\
			char_check/ft_isprint.c	char_check/ft_iswhitespace.c				\
			\
			char_operation/ft_tolower.c	char_operation/ft_toupper.c				\
			\
			get_next_line/get_next_line.c	get_next_line/get_next_line_utils.c	\
			\
			int/ft_abs.c	int/ft_itoa.c 										\
			\
			linked_list/ft_lstnew.c		linked_list/ft_lstadd_front.c			\
			linked_list/ft_lstsize.c	linked_list/ft_lstlast.c				\
			linked_list/ft_lstmap.c		linked_list/ft_lstdelone.c				\
			linked_list/ft_lstclear.c	linked_list/ft_lstiter.c				\
			linked_list/ft_lstadd_back.c										\
			\
			mem_operation/ft_memchr.c	mem_operation/ft_memcmp.c				\
			mem_operation/ft_memcpy.c	mem_operation/ft_memmove.c				\
			mem_operation/ft_memset.c 	mem_operation/ft_bzero.c				\
			\
			print/ft_printf.c	print/ft_printnbr.c		print/ft_printstr.c		\
			print/print_hex.c	print/ft_printchar.c	print/ft_putchar_fd.c	\
			print/ft_error.c	print/ft_putendl_fd.c	print/ft_putnbr_fd.c	\
			print/ft_putstr_fd.c												\
			\
			str_to_num/ft_atoi_safe.c	str_to_num/ft_atoi.c					\
			str_to_num/ft_atol.c 												\
			\
			string/ft_strchr.c	string/ft_strdup.c	string/ft_strlcat.c			\
			string/ft_strlcpy.c	string/ft_strlen.c	string/ft_strncmp.c			\
			string/ft_strnstr.c	string/ft_strrchr.c	string/ft_striteri.c		\
			string/ft_strtrim.c	string/ft_strjoin.c	string/ft_strjoin_free.c	\
			string/ft_strmapi.c	string/ft_split.c	string/ft_substr.c

SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= include

OBJ_FILES	= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
DEP_FILES	= $(OBJ_FILES:.o=.d)

SRC_SUBDIR	= $(shell find $(SRC_DIR) -type d)
OBJ_SUBDIR	= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC_SUBDIR))
		
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -MMD -MP

#--RULES------------------------------------------------------------------------

all: objdir $(NAME)

$(NAME): $(OBJ_FILES)
	@ar -rcs $@ $^

objdir:
	@mkdir -p $(OBJ_SUBDIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

-include $(DEP_FILES)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all objdir clean fclean re