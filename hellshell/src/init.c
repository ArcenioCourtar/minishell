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

void	init_dat(t_data *dat, char **envp)
{
	dat->input = NULL;
	dat->envlist = init_envlst(envp);
	dat->envp = NULL;
	dat->envp = set_envp(dat->envlist, dat->envp);
	dat->h_lst = init_history_list();
	dat->cmd_lst = init_command_list();
	dat->varlist = NULL;
	init_builtins_list(dat->builtin_index);
}
