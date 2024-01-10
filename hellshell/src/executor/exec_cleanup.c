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

void	bash_status_filter(int *status)
{
	*status = WEXITSTATUS(*status);
	if (*status != 0)
	{
		if (*status == 126)
			*status = 126;
		else if (*status == 127)
			*status = 127;
		else if (*status == 2)
			*status = 2;
		else
			*status = 1;
	}
	else
		*status = 0;
}

void	wait_for_all(t_data *dat)
{
	int			status;
	t_cmdlst	*tmp;

	tmp = *(dat->cmd_lst);
	if (g_signal == SIGINT)
		status = 128 + 2;
	else
	{
		while (tmp != NULL)
		{
			waitpid(tmp->pid, &status, 0);
			tmp = tmp->next;
		}
		if (WIFEXITED(status))
			bash_status_filter(&status);
		else
			status = 128 + WTERMSIG(status);
	}
	assign_exit_val(dat->exit_code, status);
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
