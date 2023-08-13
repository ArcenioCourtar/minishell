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

	i = 0;
	while (i < BT_NUM)
	{
		if (strncmp(arg, builtin_index[i], 10) == 0)
			return (i);
		i++;
	}
	return (i);
}

static bool	check_builtin(t_data *dat, t_exec *exec)
{
	t_cmdlst	*cmd;

	cmd = *(dat->cmd_lst);
	if (exec->fork_num != 1)
		return (false);
	if (cmd->abs_path == true)
		return (false);
	if (is_builtin(dat->builtin_index, cmd->argv[0]) == BT_NUM)
		return (false);
	return (true);
}

void	run_builtin(t_data *dat)
{
	int			index;
	t_cmdlst	*cmd;

	cmd = *(dat->cmd_lst);
	index = is_builtin(dat->builtin_index, cmd->argv[0]);
	dat->builtin_ptrs[index](dat);
}

/*
	program flow notes:
	Any error involving redirects prevents the associated command from running
*/
void	executor(t_data *dat)
{
	t_exec	exec;

	exec.fork_num = count_forks(dat->cmd_lst);
	// Check redirect permissions here? I still need to create forks,
	// but can skip execution and file creation if permissions or files not
	// existing cause an error
	if (check_builtin(dat, &exec))
	{
		run_builtin(dat);
		return ;
	}
	else
	{
		if (!find_pathvar(dat->envp, &exec))
			exit(EXIT_FAILURE);
		create_forks(dat, &exec);
		close_and_free(dat, &exec);
		wait_for_all(exec.fork_num);
	}
}
