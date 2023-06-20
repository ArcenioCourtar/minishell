/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 16:34:53 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/20 15:26:30 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlst;

	newlst = (t_list *)malloc(sizeof(t_list));
	if (newlst == 0)
		return (0);
	newlst->content = content;
	newlst->next = 0;
	return (newlst);
}
