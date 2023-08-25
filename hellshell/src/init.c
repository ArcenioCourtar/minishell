/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 14:25:02 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/28 14:25:02 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

void	init_builtins_list(char builtin_index[BT_NUM][10])
{
	ft_strlcpy(builtin_index[0], "var_ass", 10);
	ft_strlcpy(builtin_index[1], "echo", 10);
	ft_strlcpy(builtin_index[2], "cd", 10);
	ft_strlcpy(builtin_index[3], "pwd", 10);
	ft_strlcpy(builtin_index[4], "export", 10);
	ft_strlcpy(builtin_index[5], "unset", 10);
	ft_strlcpy(builtin_index[6], "env", 10);
	ft_strlcpy(builtin_index[7], "exit", 10);
	ft_strlcpy(builtin_index[8], "var", 10);
}

void	init_builtin_ptrs(t_builtin_func builtin_ptrs[BT_NUM])
{
	builtin_ptrs[0] = &builtin_var_assign;
	builtin_ptrs[1] = &builtin_echo;
	builtin_ptrs[2] = &builtin_cd;
	builtin_ptrs[3] = &builtin_pwd;
	builtin_ptrs[4] = &builtin_export;
	builtin_ptrs[5] = &builtin_unset;
	builtin_ptrs[6] = &builtin_env;
	builtin_ptrs[7] = &builtin_exit;
	builtin_ptrs[8] = &builtin_var;
}

void	init_dat(t_data *dat, char **envp)
{
	dat->input = NULL;
	dat->envlist = init_envlst(envp);
	dat->envp = NULL;
	dat->envp = set_envp(dat->envlist, dat->envp);
	dat->h_lst = init_history_list();
	dat->cmd_lst = init_command_list();
	dat->varlist = newnode_env("?=0");
	init_builtins_list(dat->builtin_index);
	init_builtin_ptrs(dat->builtin_ptrs);
}
