/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_list_functions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 11:15:01 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/25 11:15:01 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

staic t_freelst	*to_freelstnew(char *content)
{
	t_freelst	*newlst;

	newlst = (t_freelst *)malloc(sizeof(t_freelst));
	if (!newlst)
		return (NULL);
	newlst->string = content;
	newlst->next = NULL;
	return (newlst);
}

static t_freelst	*to_freelstlast(t_freelst *lst)
{
	if (!lst)
		return (NULL);
	else if (!lst->next)
		return (lst);
	else
		while (lst->next)
			lst = lst->next;
	return (lst);
}

static void	to_freelstadd_back(t_freelst **lst, t_freelst *new)
{
	t_freelst	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		tmp = to_freelstlast(*lst);
		tmp->next = new;
	}
}

void	to_freelstfree(t_freelst **lst)
{
	t_freelst	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->string);
		free(*lst);
		*lst = tmp;
	}
}

void	add_to_free_lst(t_data *data, char *content)
{
	t_freelst	*tmp;

	tmp = to_freelstnew(content);
	to_freelstadd_back(data->free_lst, tmp);
}
