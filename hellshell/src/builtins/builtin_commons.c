/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_commons.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/29 14:39:41 by acourtar      #+#    #+#                 */
/*   Updated: 2023/10/29 14:39:41 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

/*
	Function checking if variable name given is valid.
	Used for export, unset, and shell variable assignment.
	VAR NAME RULES:
	- only alphanumeric characters and "_" allowed
	- The first character cannot be a digit
*/
bool	identifier_check(char *arg)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
