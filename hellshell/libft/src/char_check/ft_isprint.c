/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:23:52 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/12 17:09:48 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Checks if the character is printable
 * @param c The character to check
 * @return 1 if the character is printable, 0 if not
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
