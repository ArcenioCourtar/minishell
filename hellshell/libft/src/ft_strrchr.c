/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:50 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 18:24:13 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*last;

	i = 0;
	last = 0;
	while (i <= ft_strlen((char *)s))
	{
		if (s[i] == (char)c)
			last = &((char *)s)[i];
		i++;
	}
	return (last);
}
