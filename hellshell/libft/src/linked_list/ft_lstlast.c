/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:40:10 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/19 17:48:37 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns the last element of a list
 * @param lst The beginning of the list
 * @return The last element of the list
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	else if (!lst->next)
		return (lst);
	else
		while (lst->next)
			lst = lst->next;
	return (lst);
}
