/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_err.c                                    :+:    :+:            */
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

int		ft_printnbr_err(long int n);
void	ft_printchar_err(char c);
int		ft_printstr_err(char *s);
int		print_hex_err(unsigned long long hex, char x);

int	print_argument_err(const char *s, int i, va_list ap)
{
	if (s[i] == 'c')
		ft_printchar_err(va_arg(ap, int));
	else if (s[i] == 's')
		return (ft_printstr_err(va_arg(ap, char *)));
	else if (s[i] == 'p')
		return (ft_printstr_err("0x")
			+ print_hex_err(va_arg(ap, unsigned long long), 'x'));
	else if (s[i] == 'd')
		return (ft_printnbr_err(va_arg(ap, int)));
	else if (s[i] == 'i')
		return (ft_printnbr_err(va_arg(ap, int)));
	else if (s[i] == 'u')
		return (ft_printnbr_err(va_arg(ap, unsigned int)));
	else if (s[i] == 'x' || s[i] == 'X')
		return (print_hex_err(va_arg(ap, unsigned int), s[i]));
	else if (s[i] == '%')
		ft_printchar_err(s[i]);
	return (1);
}

int	ft_printf_err(const char *s, ...)
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
			ft_printchar_err(s[i]);
			printed_count++;
		}
		else if (s[i] == '%' && s[i + 1])
		{
			printed_count += print_argument_err(s, i + 1, ap);
			i++;
		}
		i++;
	}
	va_end(ap);
	return (printed_count);
}
