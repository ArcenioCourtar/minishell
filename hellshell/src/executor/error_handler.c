/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 14:14:38 by acourtar      #+#    #+#                 */
/*   Updated: 2023/09/12 14:14:38 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include "parser.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>

void	assign_exit_val(t_envlst *exit_code, int errnum)
{
	free(exit_code->value);
	exit_code->value = ft_itoa(errnum);
	if (!exit_code->value)
		exit(EXIT_FAILURE);
}
