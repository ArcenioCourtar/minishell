/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printstr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 17:15:15 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/31 14:07:20 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		return (ft_printstr("(null)"));
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
