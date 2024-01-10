/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:05:35 by acourtar      #+#    #+#                 */
/*   Updated: 2024/01/10 16:05:35 by acourtar      ########   odam.nl         */
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

int	heredoc_break_conditions(char *input, char *delim)
{
	if (!input)
	{
		printf("heredoc delimited by EOF\n");
		return (1);
	}
	if (ft_strlen(delim) == 0 && ft_strlen(input) == 0)
		return (1);
	if (ft_strncmp(delim, input, ft_strlen(delim) + 1) == 0)
		return (1);
	return (0);
}

void	create_forks_close_pipe(t_cmdlst *node)
{
	node->pipe_used = false;
	close(node->pipe[0]);
	close(node->pipe[1]);
}

void	post_fork_checks(t_data *dat, t_exec *exec, t_cmdlst *tmp)
{
	if (tmp->pid == -1)
		exit(EXIT_FAILURE);
	if (tmp->pid == 0)
		exec_fork(dat, exec);
	if (tmp->next == NULL && tmp->prev)
		create_forks_close_pipe(tmp->prev);
}
