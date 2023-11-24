/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 16:10:25 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/02/10 13:23:42 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Prints a formatted string to stdout
 * @param s The string to print
 * @param ap The argument list
 * @return The number of characters printed
 */
static int	print_argument(const char *s, int i, va_list ap)
{
	if (s[i] == 'c')
		ft_printchar(va_arg(ap, int));
	else if (s[i] == 's')
		return (ft_printstr(va_arg(ap, char *)));
	else if (s[i] == 'p')
		return (ft_printstr("0x")
			+ print_hex(va_arg(ap, unsigned long long), 'x'));
	else if (s[i] == 'd')
		return (ft_printnbr(va_arg(ap, int)));
	else if (s[i] == 'i')
		return (ft_printnbr(va_arg(ap, int)));
	else if (s[i] == 'u')
		return (ft_printnbr(va_arg(ap, unsigned int)));
	else if (s[i] == 'x' || s[i] == 'X')
		return (print_hex(va_arg(ap, unsigned int), s[i]));
	else if (s[i] == '%')
		ft_printchar(s[i]);
	return (1);
}

/**
 * @brief Prints a formatted string to stdout
 * @param s The string to print
 * @return The number of characters printed
 */
int	ft_printf(const char *s, ...)
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
			ft_printchar(s[i]);
			printed_count++;
		}
		else if (s[i] == '%' && s[i + 1])
		{
			printed_count += print_argument(s, i + 1, ap);
			i++;
		}
		i++;
	}
	va_end(ap);
	return (printed_count);
}
