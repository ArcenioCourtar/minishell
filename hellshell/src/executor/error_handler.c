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

void	msg_err_exit(char *msg1, char *msg2, int errnum)
{
	if (msg2 == NULL)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", msg1, strerror(errnum));
	else
		ft_fd_printf(STDERR_FILENO, "%s: %s: %s\n", msg1, msg2, \
		strerror(errnum));
	exit(errnum);
}

void	msg_err_noexit(char *msg1, char *msg2, int errnum)
{
	if (msg2 == NULL)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", msg1, strerror(errnum));
	else
		ft_fd_printf(STDERR_FILENO, "%s: %s: %s\n", msg1, msg2, \
		strerror(errnum));
}

void	msg_err_cust_exit(char *msg1, char *msg2, char *errmsg, int errnum)
{
	if (msg2 == NULL)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", msg1, errmsg);
	else
		ft_fd_printf(STDERR_FILENO, "%s: %s: %s\n", msg1, msg2, errmsg);
	exit(errnum);
}

void	msg_err_cust_noexit(char *msg1, char *msg2, char *errmsg)
{
	if (msg2 == NULL)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", msg1, errmsg);
	else
		ft_fd_printf(STDERR_FILENO, "%s: %s: %s\n", msg1, msg2, errmsg);
}

// Make sure I cannot unset ?
void	assign_exit_val(t_envlst *exit_code, int errnum)
{
	free(exit_code->value);
	exit_code->value = ft_itoa(errnum);
	if (!exit_code->value)
		exit(EXIT_FAILURE);
}
