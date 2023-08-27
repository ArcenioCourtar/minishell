/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env_var_assign.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 19:00:22 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/28 19:00:22 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

void	builtin_env(t_data *dat, t_exec *exec)
{
	int	i;

	(void) exec;
	i = 0;
	while (dat->envp[i])
	{
		printf("%s\n", dat->envp[i]);
		i++;
	}
}

void	builtin_var_assign(t_data *dat, t_exec *exec)
{
	t_envlst	*new;

	new = check_var_existence(dat->varlist, exec->my_node->argv[0]);
	if (new == NULL)
	{
		new = check_var_existence(dat->envlist, exec->my_node->argv[0]);
		if (new == NULL)
		{
			new = newnode_env(exec->my_node->argv[0]);
			envlst_addback(dat->varlist, new);
		}
		else
		{
			change_existing_val(new, exec->my_node->argv[0]);
			dat->envp = set_envp(dat->envlist, dat->envp);
		}
	}
	else
	{
		change_existing_val(new, exec->my_node->argv[0]);
	}
}

void	builtin_var(t_data *dat, t_exec *exec)
{
	(void) exec;
	print_envlst(dat->varlist);
}
