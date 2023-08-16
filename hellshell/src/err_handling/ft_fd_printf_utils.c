/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fd_printf_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 15:06:54 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/16 15:06:54 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ft_fd_printchar(int fd, char c)
{
	write(fd, &c, 1);
}

int	ft_fd_printnbr(int fd, long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_fd_printchar(fd, '-');
		n = -n;
		count++;
	}
	if (n >= 10)
	{
		count += ft_fd_printnbr(fd, n / 10);
	}
	ft_fd_printchar(fd, (n % 10) + '0');
	count++;
	return (count);
}

int	ft_fd_printstr(int fd, char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		return (ft_fd_printstr(fd, "(null)"));
	}
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	fd_print_hex(int fd, unsigned long long hex, char x)
{
	int	count;

	count = 0;
	if (hex >= 16)
	{
		count += fd_print_hex(fd, hex / 16, x);
		count += fd_print_hex(fd, hex % 16, x);
	}
	else
	{
		if (hex <= 9)
		{
			ft_fd_printchar(fd, hex + '0');
			count++;
		}
		else
		{
			if (x == 'x')
				ft_fd_printchar(fd, hex - 10 + 'a');
			else
				ft_fd_printchar(fd, hex - 10 + 'A');
			count++;
		}
	}
	return (count);
}
