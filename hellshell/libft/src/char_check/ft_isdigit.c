/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 16:38:18 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 15:06:37 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if the character is a digit
 * @param c The character to check
 * @return 1 if the character is a digit, 0 if not
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
