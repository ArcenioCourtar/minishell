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

// bool	compare_token(char **tokens, int n, const char *str)
// {
	
// }

// int	first_command(char **tokens)
// {
	
// }

void	execute_command(t_data *dat)
{
	int	i;

	i = 0;
	if (dat->tok_count == 0)
	{
		printf("no commands\n");
		return ;
	}
	if (!ft_strncmp(dat->input, "env", 3))
		builtin_env(dat->envp);
	if (!ft_strncmp(dat->input, "history", 8))
		print_history_list(dat->h_lst);
}

void	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
