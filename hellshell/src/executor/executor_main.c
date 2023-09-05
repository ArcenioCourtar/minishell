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

// need to check for invalid var names?
bool	is_var_assignment(char *arg)
{
	if (arg[0] != '=' && ft_strchr(arg, '=') != 0)
		return (true);
	return (false);
}

int	is_builtin(char builtin_index[BT_NUM][10], char *arg)
{
	int	i;

	if (is_var_assignment(arg) == true)
	{
		return (0);
	}
	i = 1;
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

void	builtin_prep(t_data *dat, t_exec *exec)
{
	exec->my_node = *(dat->cmd_lst);
}

// void	set_redirects(t_data *dat, t_exec *exec)
// {

// }

/*
	program flow notes:
	Any error involving redirects prevents the associated command from running
*/
void	executor(t_data *dat)
{
	t_exec	exec;

	exec.fork_num = count_forks(dat->cmd_lst);
	builtin_prep(dat, &exec);
	if (check_builtin(dat, exec.my_node) && exec.fork_num == 1)
	{
		run_builtin(dat, &exec);
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
