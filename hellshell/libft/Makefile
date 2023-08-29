# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/06 13:32:03 by ovan-rhe      #+#    #+#                  #
#    Updated: 2023/06/20 13:35:47 by ovan-rhe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a

SRC_FILES =	free_double_array.c \
			ft_abs.c \
			ft_atoi_safe.c \
			ft_atoi.c \
			ft_atol.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_error.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_iswhitespace.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strjoin_free.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_striteri.c \
			ft_strmapi.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_printf.c \
			ft_printnbr.c \
			ft_printstr.c \
			print_hex.c \
			ft_printchar.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c

SRC 	= $(addprefix src/, $(SRC_FILES))
OBJS 	= $(SRC:.c=.o)
		
CFLAGS	= -Wall -Wextra -Werror
HEADERS	= -I include
CC		= gcc
RM		= rm -f


all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re