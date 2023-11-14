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

void	wait_for_all(t_data *dat)
{
	int			status;
	t_cmdlst	*tmp;

	tmp = *(dat->cmd_lst);
	while (tmp != NULL)
	{
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
			status = 1;
		else
			status = 0;
	}
	else
		status = 128 + WTERMSIG(status);
	assign_exit_val(dat->exit_code, status);
}

void	close_all_pipes(t_data *dat)
{
	t_cmdlst	*tmp;

	tmp = *(dat->cmd_lst);
	while (tmp->next != NULL)
	{
		close(tmp->pipe[0]);
		close(tmp->pipe[1]);
		tmp = tmp->next;
	}
}

void	free_path_list(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->path_avail == true && exec->path_list[i])
	{
		free(exec->path_list[i]);
		i++;
	}
	free(exec->path_list);
}
