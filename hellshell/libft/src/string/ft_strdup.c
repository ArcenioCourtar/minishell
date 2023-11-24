/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 15:18:05 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/11/10 12:08:39 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates sufficient memory for a copy of the string s1, does the copy,
 * and returns a pointer to it. The pointer may subsequently be used as an
 * argument to the function free(3). If insufficient memory is available, NULL
 * is returned and errno is set to ENOMEM.
 * @param s1 The string to duplicate
 * @return The pointer to the new string
 */
char	*ft_strdup(const char *s1)
{
	size_t	strlen;
	char	*ptr;
	int		i;

	strlen = ft_strlen((char *)s1);
	ptr = (char *)malloc(sizeof(char) * (strlen + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
