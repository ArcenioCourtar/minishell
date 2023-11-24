/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printnbr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 17:32:54 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/31 14:07:17 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Prints a number
 * @param n The number to print
 * @return The number of characters printed
 */
int	ft_printnbr(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_printchar('-');
		n = -n;
		count++;
	}
	if (n >= 10)
	{
		count += ft_printnbr(n / 10);
	}
	ft_printchar((n % 10) + '0');
	count++;
	return (count);
}
