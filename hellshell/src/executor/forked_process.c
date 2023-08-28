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

	tmp = *(dat->cmd_lst);
	if (is_builtin(dat->builtin_index, tmp->argv[0]) != BT_NUM)
		run_builtin(dat, exec);
}

// TODO: more robust error handling
// norm
void	find_path(t_exec *exec)
{
	int		i;

	exec->cmd = malloc(exec->path_maxlen + \
	ft_strlen(exec->my_node->argv[0]) + 2);
	if (!exec->cmd)
		ft_error(errno, "hellshell: malloc");
	if (exec->path_avail == 0 || exec->my_node->abs_path == true)
	{
		ft_strlcpy(exec->cmd, exec->my_node->argv[0], \
		ft_strlen(exec->my_node->argv[0]) + 1);
		if (access(exec->my_node->argv[0], X_OK) == -1)
			ft_error(errno, "hellshell: command not found");
		return ;
	}
	i = 0;
	while (exec->path_list[i])
	{
		ft_strlcpy(exec->cmd, exec->path_list[i], \
		ft_strlen(exec->path_list[i]) + 1);
		ft_strlcpy(exec->cmd + ft_strlen(exec->path_list[i]), "/", 2);
		ft_strlcpy(exec->cmd + ft_strlen(exec->path_list[i]) + 1, \
		exec->my_node->argv[0], ft_strlen(exec->my_node->argv[0]) + 1);
		if (access(exec->cmd, X_OK) == 0)
			return ;
		i++;
	}
	ft_error(errno, "hellshell: command not found");
}

void	dup_pipes(t_exec *exec)
{
	t_cmdlst	*my_node;

	my_node = exec->my_node;
	if (my_node->prev)
	{
		close(my_node->prev->pipe[1]);
		dup2(my_node->prev->pipe[0], my_node->fd_in);
		close(my_node->prev->pipe[0]);
	}
	if (my_node->next)
	{
		close(my_node->pipe[0]);
		dup2(my_node->pipe[1], my_node->fd_out);
		close(my_node->pipe[1]);
	}
}

void	exec_fork(t_data *dat, t_exec *exec)
{
	dup_pipes(exec);
	forked_builtin(dat, exec);
	find_path(exec);
	execve(exec->cmd, exec->my_node->argv, dat->envp);
	exit(EXIT_SUCCESS);
}

void	create_forks(t_data *dat, t_exec *exec)
{
	t_cmdlst	*tmp;
	// int			i;

	tmp = *(dat->cmd_lst);
	while (tmp)
	{
		// i = 0;
		if (tmp->next != NULL)
			pipe(tmp->pipe);
		// while (tmp->redirect[i].name != NULL)
		// {
		// 	if (tmp->redirect[i].type == CMD_HEREDOC)
		// 	{
		// 		pipe(tmp->heredoc);
		// 		break ;
		// 	}
		// 	i++;
		// }
		if (tmp->prev != NULL && tmp->prev->prev != NULL)
		{
			close(tmp->prev->prev->pipe[0]);
			close(tmp->prev->prev->pipe[1]);
		}
		exec->my_node = tmp;
		tmp->pid = fork();
		if (tmp->pid == -1)
			exit(EXIT_FAILURE);
		if (tmp->pid == 0)
			exec_fork(dat, exec);
		if (tmp->next == NULL && tmp->prev)
		{
			close(tmp->prev->pipe[0]);
			close(tmp->prev->pipe[1]);
		}
		tmp = tmp->next;
	}
}
