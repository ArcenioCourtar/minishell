/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forked_process.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/13 18:20:00 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/13 18:20:00 by acourtar      ########   odam.nl         */
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

void	exec_fork(t_data *dat, t_exec *exec)
{
	printf("child, my node %p\n", exec->my_node);
	exit(EXIT_SUCCESS);
}

void	create_forks(t_data *dat, t_exec *exec)
{
	t_cmdlst	*tmp;

	tmp = *(dat->cmd_lst);
	while (tmp)
	{
		exec->my_node = tmp;
		tmp->pid = fork();
		if (tmp->pid == -1)
			exit(EXIT_FAILURE);
		if (tmp->pid == 0)
			exec_fork(dat, exec);
		tmp = tmp->next;
	}
}
