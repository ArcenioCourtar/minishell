/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_list_functies.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 17:36:11 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/09 17:36:11 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"

t_envlst	*varlst_new_node(char *variable)
{
	t_envlst	*new_node;

	new_node = (t_envlst *)malloc(sizeof(t_envlst));
	if (!new_node)
		ft_error(errno, strerror(errno));
	new_node->size = ft_strlen(variable) + 1;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->name = variable;
	return (new_node);
}

t_envlst	*varlst_last(t_envlst *var_lst)
{
	if (!var_lst->next)
		return (var_lst);
	else
		while (var_lst->next)
			var_lst = var_lst->next;
	return (var_lst);
}

void	varlst_add_back(t_data *data, t_envlst *new_node)
{
	t_envlst	*tmp;

	if (!data->varlist)
		data->varlist = new_node;
	else
	{
		tmp = varlst_last(data->varlist);
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}
