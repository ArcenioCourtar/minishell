/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_functions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 15:10:24 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/28 15:10:24 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

t_toklst	*tlst_new_node(char *token)
{
	t_toklst	*new_node;

	new_node = (t_toklst *)malloc(sizeof(t_toklst));
	if (!new_node)
		ft_error(errno, strerror(errno));
	new_node->token = token;
	new_node->type = get_token_type(token);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

static t_toklst	*token_lstlast(t_toklst *t_lst)
{
	if (!t_lst)
		return (NULL);
	else if (!t_lst->next)
		return (t_lst);
	else
		while (t_lst->next)
			t_lst = t_lst->next;
	return (t_lst);
}

void	token_lstadd_back(t_toklst **t_lst_head, t_toklst *new_node)
{
	t_toklst	*tmp;

	if (!*t_lst_head)
	{
		*t_lst_head = new_node;
		return ;
	}
	else
	{
		tmp = token_lstlast(*t_lst_head);
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}
