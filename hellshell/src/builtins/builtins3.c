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

void	builtin_env(t_data *dat)
{
	int	i;

	i = 0;
	while (dat->envp[i])
	{
		printf("%s\n", dat->envp[i]);
		i++;
	}
}

void	builtin_echo(t_data *dat)
{
	t_envlst	*tmp;

	tmp = dat->envlist;
	if (dat->tokens[2][0] == '$')
	{
		while (tmp && dat->tok_count == 4)
		{
			if (!ft_strnstr(tmp->name, dat->tokens[3], ft_strlen(tmp->name)))
			{
				printf("%s\n", tmp->value);
				return ;
			}
			tmp = tmp->next;
		}
		printf("\n");
	}
	else
		printf("%s\n", dat->tokens[2]);
}

void	builtin_pwd(t_data *dat)
{
	char	buffer[MAX_PATH];

	(void) dat;
	ft_bzero(buffer, MAX_PATH);
	if (getcwd(buffer, MAX_PATH) == NULL)
		printf("%s\n", strerror(errno));
	else
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

void	builtin_exit(t_data *dat)
{
	(void) dat;
	exit(EXIT_SUCCESS);
}
