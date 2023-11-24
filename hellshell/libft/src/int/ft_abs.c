/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 17:33:01 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/04/24 17:33:15 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Returns the absolute value of an integer
 * @param i The integer to return the absolute value of
 */
int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}
