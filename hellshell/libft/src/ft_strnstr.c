/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:36:46 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/14 12:54:27 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	j = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
	{
		return ((char *)haystack);
	}
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[j])
		{
			if (ft_strncmp((haystack + i), needle, needle_len) == 0
				&& i + needle_len <= len)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
