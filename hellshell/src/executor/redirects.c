/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 18:52:38 by acourtar      #+#    #+#                 */
/*   Updated: 2023/11/16 18:52:38 by acourtar      ########   odam.nl         */
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

static int	red_in_wrapper(t_cmdlst *node, int i)
{
	node->fd_in = open(node->redirect[i].name, O_RDONLY);
	if (node->fd_in == -1)
	{
		ft_printf_err("hellshell: %s: %s\n", node->redirect[i].name, \
		strerror(errno));
		return (errno);
	}
	return (0);
}

static int	red_out_wrapper(t_cmdlst *node, int i)
{
	if (node->redirect[i].type == REDOUT)
		node->fd_out = open(node->redirect[i].name, O_WRONLY | O_CREAT | \
		O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		node->fd_out = open(node->redirect[i].name, O_WRONLY | O_CREAT | \
		O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (node->fd_out == -1)
	{
		ft_printf_err("hellshell: %s: %s\n", node->redirect[i].name, \
		strerror(errno));
		return (errno);
	}
	return (0);
}

// parent boolean is there to signify if the redirects are run from the
// parent process or not. If they are, don't exit.
int	redirects(t_exec *exec)
{
	t_cmdlst	*node;
	int			i;

	node = exec->my_node;
	if (node->redirect == NULL)
		return (0);
	i = 0;
	while (node->redirect[i].name)
	{
		if (node->redirect[i].type == REDIN)
		{
			if (red_in_wrapper(node, i) != 0)
				return (errno);
		}
		if (node->redirect[i].type == REDOUT || \
		node->redirect[i].type == REDAPPEND)
		{
			if (red_out_wrapper(node, i) != 0)
				return (errno);
		}
		i++;
	}
	dup2(node->fd_in, STDIN_FILENO);
	dup2(node->fd_out, STDOUT_FILENO);
	return (0);
}
