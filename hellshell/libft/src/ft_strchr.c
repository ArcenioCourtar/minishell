/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:47:36 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 18:22:45 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	len_s;

	i = 0;
	len_s = ft_strlen(s);
	while (i <= len_s)
	{
		if (s[i] == (char)c)
			return (&s[i]);
		else
			i++;
	}
	return (0);
}
