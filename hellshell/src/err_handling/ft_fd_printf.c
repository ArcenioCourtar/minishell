/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fd_printf.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:02:57 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/16 15:02:57 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

int		ft_fd_printnbr(int fd, long int n);
void	ft_fd_printchar(int fd, char c);
int		ft_fd_printstr(int fd, char *s);
int		fd_print_hex(int fd, unsigned long long hex, char x);

int	fd_print_argument(int fd, const char *s, int i, va_list ap)
{
	if (s[i] == 'c')
		ft_fd_printchar(fd, va_arg(ap, int));
	else if (s[i] == 's')
		return (ft_fd_printstr(fd, va_arg(ap, char *)));
	else if (s[i] == 'p')
		return (ft_fd_printstr(fd, "0x")
			+ fd_print_hex(fd, va_arg(ap, unsigned long long), 'x'));
	else if (s[i] == 'd')
		return (ft_fd_printnbr(fd, va_arg(ap, int)));
	else if (s[i] == 'i')
		return (ft_fd_printnbr(fd, va_arg(ap, int)));
	else if (s[i] == 'u')
		return (ft_fd_printnbr(fd, va_arg(ap, unsigned int)));
	else if (s[i] == 'x' || s[i] == 'X')
		return (fd_print_hex(fd, va_arg(ap, unsigned int), s[i]));
	else if (s[i] == '%')
		ft_fd_printchar(fd, s[i]);
	return (1);
}

int	ft_fd_printf(int fd, const char *s, ...)
{
	int		i;
	int		printed_count;
	va_list	ap;

	i = 0;
	printed_count = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] != '%')
		{
			ft_fd_printchar(fd, s[i]);
			printed_count++;
		}
		else if (s[i] == '%' && s[i + 1])
		{
			printed_count += fd_print_argument(fd, s, i + 1, ap);
			i++;
		}
		i++;
	}
	va_end(ap);
	return (printed_count);
}
