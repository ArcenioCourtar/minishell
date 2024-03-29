/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:46:01 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/06 14:46:24 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts an uppercase letter to lowercase
 * @param c The character to convert
 * @return The lowercase character
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
