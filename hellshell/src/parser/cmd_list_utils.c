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

t_cmd	*cmdlst_new_node(char *command)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		ft_error(errno, strerror(errno));
	new_node->command = command;
	new_node->argv = NULL;
	new_node->envp = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_cmd	*cmd_lstlast(t_cmd *cmd_lst)
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

void	cmd_lstadd_back(t_cmd **cmd_lst_head, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (!*cmd_lst_head)
	{
		*cmd_lst_head = new_node;
		return ;
	}
	else
	{
		tmp = cmd_lstlast(*cmd_lst_head);
		tmp->next = new_node;
	}
}
