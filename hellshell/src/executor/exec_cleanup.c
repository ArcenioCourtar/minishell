/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cleanup.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/13 18:19:54 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/13 18:19:54 by acourtar      ########   odam.nl         */
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

void	wait_for_all(int fork_amount)
{
	int	i;

	i = 0;
	while (i < fork_amount)
	{
		wait(0);
		i++;
	}
	printf("done waiting\n");
}

void	close_and_free(t_data *dat, t_exec *exec)
{
	t_cmdlst	*tmp;
	int			i;

	tmp = *(dat->cmd_lst);
	while (tmp->next != NULL)
	{
		close(tmp->pipe[0]);
		close(tmp->pipe[1]);
		tmp = tmp->next;
	}
	i = 0;
	while (exec->path_avail == true && exec->path_list[i])
	{
		free(exec->path_list[i]);
		i++;
	}
	free(exec->path_list);
}
