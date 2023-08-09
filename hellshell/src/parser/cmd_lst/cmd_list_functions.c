/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_list_functions.c                               :+:    :+:            */
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

t_cmdlst	*cmdlst_new_node(void)
{
	t_cmdlst	*new_node;

	new_node = (t_cmdlst *)ft_calloc(sizeof(t_cmdlst), 1);
	if (!new_node)
		ft_error(errno, strerror(errno));
	return (new_node);
}

static t_cmdlst	*cmdlst_last(t_cmdlst *cmd_lst)
{
	if (!cmd_lst->next)
		return (cmd_lst);
	else
		while (cmd_lst->next)
			cmd_lst = cmd_lst->next;
	return (cmd_lst);
}

void	cmdlst_add_back(t_cmdlst **cmd_lst_head, t_cmdlst *new_node)
{
	t_cmdlst	*tmp;

	if (!*cmd_lst_head)
		*cmd_lst_head = new_node;
	else
	{
		tmp = cmdlst_last(*cmd_lst_head);
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}

void	toklst_del_node(t_toklst **token)
{
	t_toklst	*current_tok;

	if ((*token)->prev)
	{
		current_tok = (*token)->prev;
		if ((*token)->next)
		{
			(*token)->prev->next = (*token)->next;
			(*token)->next->prev = (*token)->prev;
		}
		else
			(*token)->prev->next = NULL;
	}
	else if ((*token)->next)
	{
		(*token)->next->prev = NULL;
		current_tok = (*token)->next;
	}
	else
		current_tok = NULL;
	free((*token)->token);
	free(*token);
	*token = current_tok;
}

void	cmdlst_free_node(t_cmdlst *node)
{
	int	i;

	i = 0;
	while (node->argv[i])
	{
		free(node->argv[i]);
		i++;
	}
	free(node->argv);
	free(node->redirect);
	free(node);
}
