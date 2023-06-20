/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 16:30:07 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 15:08:24 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;

	i = 0;
	dstlen = ft_strlen(dst);
	if (dstsize == 0)
		return (dstsize + ft_strlen(src));
	if (dstsize > dstlen)
	{
		while (i < dstsize - dstlen - 1 && src[i] != '\0')
		{
			dst[dstlen + i] = src[i];
			i++;
		}
		dst[dstlen + i] = '\0';
	}
	if (dstsize < dstlen)
		return (dstsize + ft_strlen(src));
	else
		return (dstlen + ft_strlen(src));
}
