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

void	init_dat(t_data *dat, char **envp)
{
	dat->input = NULL;
	dat->envlist = init_envlst(envp);
	dat->envp = NULL;
	dat->envp = set_envp(dat->envlist, dat->envp);
	dat->h_lst = init_history_list();
	dat->cmd_lst = init_command_list();
}
