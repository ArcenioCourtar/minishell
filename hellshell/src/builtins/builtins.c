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
