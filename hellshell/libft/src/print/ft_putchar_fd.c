/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 17:13:35 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 17:18:15 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes a character to a file descriptor
 * @param c The character to write
 * @param fd The file descriptor to write to
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
