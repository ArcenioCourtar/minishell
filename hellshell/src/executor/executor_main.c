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

int	is_builtin(char builtin_index[BT_NUM][10], char *arg)
{
	int	i;

	if (arg == NULL)
		return (BT_NUM);
	i = 0;
	while (i < BT_NUM)
	{
		if (strncmp(arg, builtin_index[i], 10) == 0)
			return (i);
		i++;
	}
	return (i);
}

static bool	check_builtin(t_data *dat, t_cmdlst *node)
{
	if (node->abs_path == true)
		return (false);
	if (is_builtin(dat->builtin_index, node->argv[0]) == BT_NUM)
		return (false);
	return (true);
}

void	run_builtin(t_data *dat, t_exec *exec)
{
	int			index;
	t_cmdlst	*cmd;

	cmd = exec->my_node;
	index = is_builtin(dat->builtin_index, cmd->argv[0]);
	dat->builtin_ptrs[index](dat, exec);
}

void	save_old_fds(t_exec *exec)
{
	exec->in_out_fd[0] = dup(STDIN_FILENO);
	exec->in_out_fd[1] = dup(STDOUT_FILENO);
}

void	restore_old_fds(t_exec *exec)
{
	dup2(exec->in_out_fd[0], STDIN_FILENO);
	dup2(exec->in_out_fd[1], STDOUT_FILENO);
	close(exec->in_out_fd[0]);
	close(exec->in_out_fd[1]);
}
/*
	program flow notes:
	Any error involving redirects prevents the associated command from running
	TODO: Generating files with outfile redirects without a command before it.
*/
void	executor(t_data *dat)
{
	t_exec	exec;
	int		tmp;

	if (*(dat->cmd_lst) == NULL)
		return ;
	exec.exit_code = dat->varlist;
	exec.fork_num = count_forks(dat->cmd_lst);
	signals_in_process();
	exec.my_node = *(dat->cmd_lst);
	if (check_builtin(dat, exec.my_node) && exec.fork_num == 1)
	{
		save_old_fds(&exec);
		tmp = redirects(&exec, true);
		if (tmp != 0)
		{
			assign_exit_val(exec.exit_code, tmp);
			return ;
		}
		run_builtin(dat, &exec);
		restore_old_fds(&exec);
		return ;
	}
	else
	{
		if (!find_pathvar(dat->envp, &exec))
			exit(EXIT_FAILURE);
		create_forks(dat, &exec);
		close_all_pipes(dat);
		free_path_list(&exec);
		wait_for_all(dat);
	}
}
