/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:42:39 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/12 16:09:01 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills the first n bytes of the memory area pointed to by s with the
 * constant byte c
 * @param b The memory area to write to
 * @param c The constant byte to write
 * @param len The number of bytes to write
 * @return A pointer to the memory area s
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((char *)b + i) = c;
		i++;
	}
	return (b);
}
