/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 16:41:57 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/01/09 16:59:24 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to a long integer
 * @param str The string to convert
 * @return The converted long integer
 */
long	ft_atol(const char *str)
{
	int		i;
	int		posneg;
	long	num;

	i = 0;
	posneg = 1;
	num = 0;
	if (str[i] == '-')
	{
		posneg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (posneg * num);
}
