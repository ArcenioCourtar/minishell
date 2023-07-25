/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 14:09:12 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/18 14:09:12 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

t_cmd	*cmdlst_new_node(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if (!new_node)
		ft_error(errno, strerror(errno));
	return (new_node);
}

static t_cmd	*cmdlst_last(t_cmd *cmd_lst)
{
	if (!cmd_lst)
		return (NULL);
	else if (!cmd_lst->next)
		return (cmd_lst);
	else
		while (cmd_lst->next)
			cmd_lst = cmd_lst->next;
	return (cmd_lst);
}

void	cmdlst_add_back(t_cmd **cmd_lst_head, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (!*cmd_lst_head)
	{
		*cmd_lst_head = new_node;
		return ;
	}
	else
	{
		tmp = cmdlst_last(*cmd_lst_head);
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}
