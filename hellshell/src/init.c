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
	ft_strlcpy(builtin_index[0], "echo", 10);
	ft_strlcpy(builtin_index[1], "cd", 10);
	ft_strlcpy(builtin_index[2], "pwd", 10);
	ft_strlcpy(builtin_index[3], "export", 10);
	ft_strlcpy(builtin_index[4], "unset", 10);
	ft_strlcpy(builtin_index[5], "env", 10);
	ft_strlcpy(builtin_index[6], "exit", 10);
}

void	init_builtin_ptrs(t_builtin_func builtin_ptrs[BT_NUM])
{
	builtin_ptrs[0] = &builtin_echo;
	builtin_ptrs[1] = &builtin_cd;
	builtin_ptrs[2] = &builtin_pwd;
	builtin_ptrs[3] = &builtin_export;
	builtin_ptrs[4] = &builtin_unset;
	builtin_ptrs[5] = &builtin_env;
	builtin_ptrs[6] = &builtin_exit;
}

void	init_dat(t_data *dat, char **envp)
{
	dat->input = NULL;
	dat->envlist = init_envlst(envp);
	dat->envp = NULL;
	dat->envp = set_envp(dat->envlist, dat->envp);
	dat->cmd_lst = init_command_list();
	dat->exit_code = newnode_env("?=0");
	if (!dat->exit_code)
		ft_error(errno, "malloc\n");
	dat->free_lst = (t_freelst **)ft_calloc(1, sizeof(t_freelst *));
	if (!dat->free_lst)
		ft_error(errno, "malloc\n");
	init_builtins_list(dat->builtin_index);
	init_builtin_ptrs(dat->builtin_ptrs);
}
