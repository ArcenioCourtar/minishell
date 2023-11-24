/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_hex.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 12:52:02 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/31 14:07:26 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Prints a hexadecimal number
 * @param hex The hexadecimal number to print
 * @param x The type of hexadecimal number to print
 * @return The number of characters printed
 */
int	print_hex(unsigned long long hex, char x)
{
	int	count;

	count = 0;
	if (hex >= 16)
	{
		count += print_hex(hex / 16, x);
		count += print_hex(hex % 16, x);
	}
	else
	{
		if (hex <= 9)
		{
			ft_printchar(hex + '0');
			count++;
		}
		else
		{
			if (x == 'x')
				ft_printchar(hex - 10 + 'a');
			else
				ft_printchar(hex - 10 + 'A');
			count++;
		}
	}
	return (count);
}
