/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:42:11 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/28 13:42:11 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

bool	compare_token(char **tokens, int n, const char *str)
{
	if (!ft_strncmp(tokens[n], str, ft_strlen(str)))
		return (true);
	return (false);
}

void	execute_command(t_data *dat)
{
	if (dat->tok_count == 0)
	{
		printf("no commands\n");
		return ;
	}
	if (compare_token(dat->tokens, 0, "env"))
		builtin_env(dat->envp);
	if (compare_token(dat->tokens, 0, "export"))
	{
		if (dat->tok_count == 3)
			builtin_export(dat);
		else
			builtin_env(dat->envp);
	}
	if (compare_token(dat->tokens, 0, "history"))
		print_history_list(dat->h_lst);
	if (compare_token(dat->tokens, 0, "pwd"))
		builtin_pwd();
	if (compare_token(dat->tokens, 0, "cd"))
		builtin_cd(dat);
	if (compare_token(dat->tokens, 0, "exit"))
		builtin_exit();
}
