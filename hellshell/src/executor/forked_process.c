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

void	forked_builtin(t_data *dat, t_exec *exec)
{
	t_cmdlst	*tmp;

	tmp = exec->my_node;
	if (is_builtin(dat->builtin_index, tmp->argv[0]) != BT_NUM)
	{
		run_builtin(dat, exec);
		exit(ft_atoi(dat->exit_code->value));
	}
}

void	dup_pipes(t_exec *exec)
{
	t_cmdlst	*my_node;

	my_node = exec->my_node;
	if (my_node->prev)
	{
		close(my_node->prev->pipe[1]);
		dup2(my_node->prev->pipe[0], my_node->fd_in);
	}
	if (my_node->next)
	{
		close(my_node->pipe[0]);
		dup2(my_node->pipe[1], my_node->fd_out);
	}
}

void	exec_fork(t_data *dat, t_exec *exec)
{
	int	tmp;

	dup_pipes(exec);
	tmp = redirects(exec);
	if (tmp != 0)
		exit (1);
	if (exec->my_node->argv[0] == NULL)
		exit(EXIT_SUCCESS);
	forked_builtin(dat, exec);
	find_path(exec);
	execve(exec->cmd, exec->my_node->argv, dat->envp);
	if (errno == 13)
	{
		ft_printf_err("%s: Is a directory\n", exec->my_node->argv[0]);
		exit(126);
	}
	ft_printf_err("%s: command not found\n", exec->my_node->argv[0]);
	exit(127);
}

static void	create_forks_close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

// TODO: erro checking when calling pipe()
void	create_forks(t_data *dat, t_exec *exec)
{
	t_cmdlst	*tmp;

	tmp = *(dat->cmd_lst);
	while (tmp)
	{
		if (g_signal == SIGINT)
			break ;
		if (tmp->next != NULL)
		{
			if (pipe(tmp->pipe) != 0)
				ft_printf_err("broken pipe\n");
		}
		if (tmp->prev != NULL && tmp->prev->prev != NULL)
			create_forks_close_pipe(tmp->prev->prev->pipe);
		exec->my_node = tmp;
		tmp->pid = fork();
		if (tmp->pid == -1)
			exit(EXIT_FAILURE);
		if (tmp->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			exec_fork(dat, exec);
		}
		if (tmp->next == NULL && tmp->prev)
			create_forks_close_pipe(tmp->prev->pipe);
		tmp = tmp->next;
	}
}
