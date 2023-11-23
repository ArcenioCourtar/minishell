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

void	builtin_export(t_data *dat, t_exec *exec)
{
	t_envlst	*new;

	if (exec->my_node->argv[1] == NULL)
	{
		builtin_env(dat, exec);
		return ;
	}
	if (!identifier_check(exec->my_node->argv[1]))
	{
		ft_printf_err("%s: not a valid identifier\n", exec->my_node->argv[1]);
		assign_exit_val(dat->exit_code, 1);
		return ;
	}
	if (ft_strchr(exec->my_node->argv[1], '=') == NULL)
		return ;
	new = check_var_existence(dat->envlist, exec->my_node->argv[1]);
	if (new == NULL)
	{
		new = newnode_env(exec->my_node->argv[1]);
		envlst_addback(dat->envlist, new);
	}
	else
		change_existing_val(new, exec->my_node->argv[1]);
	dat->envp = set_envp(dat->envlist, dat->envp);
	assign_exit_val(dat->exit_code, 0);
}

void	builtin_unset(t_data *dat, t_exec *exec)
{
	t_envlst	*node;

	if (exec->my_node->argv[1] == NULL)
	{
		assign_exit_val(dat->exit_code, 0);
		return ;
	}
	if (!identifier_check(exec->my_node->argv[1]))
	{
		ft_printf_err("%s: invalid parameter name\n", exec->my_node->argv[1]);
		assign_exit_val(dat->exit_code, 1);
		return ;
	}
	node = check_var_existence(dat->envlist, exec->my_node->argv[1]);
	if (node)
	{
		envlst_free_node(node);
		dat->envp = set_envp(dat->envlist, dat->envp);
		if (!dat->envp)
			exit(EXIT_FAILURE);
	}
	assign_exit_val(dat->exit_code, 0);
}
