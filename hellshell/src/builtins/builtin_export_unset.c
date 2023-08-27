/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export_unset.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 18:58:14 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/28 18:58:14 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

// TODO: need to check for invalid var names and return an error
// - add env functionality when calling with no extra args
// - norm
void	builtin_export(t_data *dat, t_exec *exec)
{
	t_envlst	*new;

	if (exec->my_node->argv[1] == NULL || exec->my_node->argv[1][0] == '=')
		return ;
	if (ft_strchr(exec->my_node->argv[1], '=') == 0)
	{
		new = check_var_existence(dat->varlist, exec->my_node->argv[1]);
		if (new)
		{
			envlst_move_node(new, dat->envlist);
			dat->envp = set_envp(dat->envlist, dat->envp);
		}
		return ;
	}
	new = check_var_existence(dat->envlist, exec->my_node->argv[1]);
	if (new == NULL)
	{
		new = check_var_existence(dat->varlist, exec->my_node->argv[1]);
		if (new)
		{
			envlst_move_node(new, dat->envlist);
			change_existing_val(new, exec->my_node->argv[1]);
		}
		else
		{
			new = newnode_env(exec->my_node->argv[1]);
			envlst_addback(dat->envlist, new);
		}
	}
	else
		change_existing_val(new, exec->my_node->argv[1]);
	dat->envp = set_envp(dat->envlist, dat->envp);
}

// Need to check for invalid input
void	builtin_unset(t_data *dat, t_exec *exec)
{
	t_envlst	*node;

	if (exec->my_node->argv[1] == NULL)
		return ;
	node = check_var_existence(dat->envlist, exec->my_node->argv[1]);
	if (node)
	{
		envlst_free_node(node);
		dat->envp = set_envp(dat->envlist, dat->envp);
		return ;
	}
	node = check_var_existence(dat->varlist, exec->my_node->argv[1]);
	if (node)
		envlst_free_node(node);
}
