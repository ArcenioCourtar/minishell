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

static int	count_forks(t_cmdlst **list)
{
	t_cmdlst	*tmp;
	int			count;

	tmp = *list;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

bool	check_builtin(t_data *dat)
{
	t_cmdlst	*cmd;

	cmd = *(dat->cmd_lst);
	if (dat->exec.fork_num != 1)
		return (false);
	if (cmd->abs_path == true)
		return (false);
	return (true);
}

void	executor(t_data *dat)
{
	dat->exec.fork_num = count_forks(dat->cmd_lst);
	if (check_builtin(dat))
		return ;
}
