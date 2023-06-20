/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 11:27:58 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/20 16:55:52 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_int_size(long int n, int size);
static void	put_in_str(char *str, long int n, int size);

char	*ft_itoa(int n)
{
	char		*str;
	int			size_n;
	long int	nb;

	nb = n;
	size_n = get_int_size(nb, 0);
	str = (char *)malloc(sizeof(char) * (size_n + 1));
	if (str == 0)
		return (0);
	if (n < 0)
	{
		str[0] = '-';
		put_in_str(str + 1, -nb, size_n - 1);
	}
	else
		put_in_str(str, nb, size_n);
	str[size_n] = '\0';
	return (str);
}

static int	get_int_size(long int n, int size)
{
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	if (n / 10 == 0)
	{
		size++;
		return (size);
	}
	else
		size = 1 + get_int_size(n / 10, size);
	return (size);
}

static void	put_in_str(char *str, long int n, int size)
{
	if (n / 10 == 0)
	{
		str[size - 1] = n + '0';
		return ;
	}
	else
		put_in_str(str, n / 10, size - 1);
	put_in_str(str, n % 10, size);
	return ;
}
