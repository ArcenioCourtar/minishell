/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins3.c                                        :+:    :+:            */
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

void	builtin_pwd(void)
{
	char	buffer[1000];

	ft_bzero(buffer, 1000);
	getcwd(buffer, 1000);
	// error checking
	printf("%s\n", buffer);
}

// TODO: handle CDPATH
void	builtin_cd(t_data *dat)
{
	if (dat->tok_count > 1)
	{
		if (chdir(dat->tokens[2]) == -1)
			printf("%s\n", strerror(errno));
	}
}

void	builtin_exit(void)
{
	exit(EXIT_SUCCESS);
}
