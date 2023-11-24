/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printchar.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 17:13:35 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/11/24 14:55:21 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Prints a character
 * @param c The character to print
 */
void	ft_printchar(char c)
{
	write(1, &c, 1);
}
