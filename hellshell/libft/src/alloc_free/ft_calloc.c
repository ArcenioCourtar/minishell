/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:49:27 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/02/16 15:41:07 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Allocates memory for an array of count elements of size bytes each
 * and returns a pointer to the allocated memory. The memory is set to zero.
 * @param count The number of elements to allocate memory for
 * @param size The size of each element
 * @return A pointer to the allocated memory
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}
