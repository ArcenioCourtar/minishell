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

t_cmdlst	**init_command_list(void)
{
	t_cmdlst	**cmd_lst_head;

	cmd_lst_head = (t_cmdlst **)malloc(sizeof(t_cmdlst *));
	if (!cmd_lst_head)
		ft_error(errno, strerror(errno));
	*cmd_lst_head = NULL;
	return (cmd_lst_head);
}

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

void	cmdlst_free(t_data *data)
{
	t_cmdlst	*tmp;
	t_cmdlst	*next;

	tmp = *(data->cmd_lst);
	while (tmp)
	{
		next = tmp->next;
		free(tmp->argv);
		if (tmp->redirect)
			free(tmp->redirect);
		free(tmp);
		tmp = next;
	}
	*(data->cmd_lst) = NULL;
}
