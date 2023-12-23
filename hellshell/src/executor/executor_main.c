/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_main.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 15:41:42 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/10 15:41:42 by acourtar      ########   odam.nl         */
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

void	exec_parent_wrapper(t_data *dat, t_exec *exec)
{
	int		tmp;

	save_old_fds(exec);
	tmp = redirects(exec);
	if (tmp != 0)
	{
		if (tmp != ENOENT)
			assign_exit_val(exec->exit_code, 2);
		else
			assign_exit_val(exec->exit_code, 1);
		return ;
	}
	run_builtin(dat, exec);
	restore_old_fds(exec);
}

void	exec_child_wrapper(t_data *dat, t_exec *exec)
{
	if (!find_pathvar(dat->envp, exec))
		exit(EXIT_FAILURE);
	create_forks(dat, exec);
	free_path_list(exec);
	wait_for_all(dat);
}

void	cleanup_heredoc_pipes(t_exec *exec)
{
	t_cmdlst	*node;

	node = exec->first_node;
	while (node)
	{
		if (node->hd_used == true)
			close(node->heredoc[0]);
		node = node->next;
	}
}

/**
 * @brief function that handles heredocs, builtins, external programs and
 * redirects.
 * @param dat main data structure
 */
void	executor(t_data *dat)
{
	t_exec	exec;

	if (*(dat->cmd_lst) == NULL)
		return ;
	exec.exit_code = dat->exit_code;
	exec.fork_num = count_forks(dat->cmd_lst);
	exec.my_node = *(dat->cmd_lst);
	exec.first_node = *(dat->cmd_lst);
	create_heredocs(dat, &exec);
	if (check_builtin(dat, exec.my_node) && exec.fork_num == 1)
		exec_parent_wrapper(dat, &exec);
	else
		exec_child_wrapper(dat, &exec);
	cleanup_heredoc_pipes(&exec);
}
