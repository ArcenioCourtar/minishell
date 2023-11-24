/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iswhitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 15:02:35 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/10/26 15:02:35 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is a whitespace character
 * @param c The character to check
 * @return 1 if the character is a whitespace character, 0 if not
 */
int	ft_iswhitespace(int c)
{
	if (c == '\f' || c == '\n' || c == '\r' || \
		c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}
