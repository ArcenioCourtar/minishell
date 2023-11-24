/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_safe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:30:25 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/04/03 16:36:30 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to an integer
 * @param str The string to convert
 * @param nbr The integer to store the result in
 * @return 1 if the conversion was successful, 0 if not
 */
int	ft_atoi_safe(const char *str, int *nbr)
{
	int		i;
	int		posneg;
	long	num;

	i = 0;
	posneg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' \
	|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		posneg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		num = (num * 10) + (str[i] - '0');
		if ((num > 2147483647 && posneg == 1) \
		|| (num > 2147483648 && posneg == -1))
			return (0);
		i++;
	}
	return (*nbr = num * posneg);
}
