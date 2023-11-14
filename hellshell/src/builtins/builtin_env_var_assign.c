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
