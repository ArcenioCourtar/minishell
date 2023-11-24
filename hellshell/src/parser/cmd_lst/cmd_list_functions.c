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

/**
 * @brief initializes the command list
 * @return pointer to the head of the command list
 */
t_cmdlst	**init_command_list(void)
{
	t_cmdlst	**cmd_lst_head;

	cmd_lst_head = (t_cmdlst **)malloc(sizeof(t_cmdlst *));
	if (!cmd_lst_head)
		ft_error(errno, strerror(errno));
	*cmd_lst_head = NULL;
	return (cmd_lst_head);
}

/**
 * @brief creates a new command list node
 * @return pointer to the new node
 */
t_cmdlst	*cmdlst_new_node(void)
{
	t_cmdlst	*new_node;

	new_node = (t_cmdlst *)ft_calloc(sizeof(t_cmdlst), 1);
	if (!new_node)
		ft_error(errno, strerror(errno));
	return (new_node);
}

/**
 * @brief returns the last node of the command list
 * @param cmd_lst pointer to the first node of the command list
 * @return pointer to the last node of the command list
 */
static t_cmdlst	*cmdlst_last(t_cmdlst *cmd_lst)
{
	if (!cmd_lst->next)
		return (cmd_lst);
	else
		while (cmd_lst->next)
			cmd_lst = cmd_lst->next;
	return (cmd_lst);
}

/**
 * @brief adds a new node to the end of the command list
 * @param cmd_lst_head pointer to the first node of the command list
 * @param new_node pointer to the new node to add
 */
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

/**
 * @brief frees the command list
 * @param data pointer to the program data struct
 */
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
