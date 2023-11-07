/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_err_utils.c                              :+:    :+:            */
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

void	ft_printchar_err(char c)
{
	write(STDERR_FILENO, &c, 1);
}

int	ft_printnbr_err(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_printchar_err('-');
		n = -n;
		count++;
	}
	if (n >= 10)
	{
		count += ft_printnbr_err(n / 10);
	}
	ft_printchar_err((n % 10) + '0');
	count++;
	return (count);
}

int	ft_printstr_err(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		return (ft_printstr_err("(null)"));
	}
	while (s[i])
	{
		write(STDERR_FILENO, &s[i], 1);
		i++;
	}
	return (i);
}

int	print_hex_err(unsigned long long hex, char x)
{
	int	count;

	count = 0;
	if (hex >= 16)
	{
		count += print_hex_err(hex / 16, x);
		count += print_hex_err(hex % 16, x);
	}
	else
	{
		if (hex <= 9)
		{
			ft_printchar_err(hex + '0');
			count++;
		}
		else
		{
			if (x == 'x')
				ft_printchar_err(hex - 10 + 'a');
			else
				ft_printchar_err(hex - 10 + 'A');
			count++;
		}
	}
	return (count);
}
