/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:12:56 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/20 17:10:33 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	len_s;

	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_calloc(1, 1));
	else if (len > len_s || start + len > len_s)
		len = len_s - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		substr[i] = ((char *)s)[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
