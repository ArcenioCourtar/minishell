/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:26:07 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/19 17:31:43 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (!lst)
		return (0);
	else
		count = 1;
	while (lst->next != 0)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
