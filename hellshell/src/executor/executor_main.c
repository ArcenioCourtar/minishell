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
	close_all_pipes(dat);
	free_path_list(exec);
	wait_for_all(dat);
}

void	run_heredoc(t_data *dat, t_exec *exec, t_cmdlst *node, char *keyword)
{
	char	*input;

	(void) dat;
	(void) exec;
	while (1)
	{
		input = readline("> ");
		if (ft_strlen(keyword) == 0 && ft_strlen(input) == 0)
			break ;
		if (ft_strncmp(keyword, input, ft_strlen(keyword) + 1) == 0)
			break ;
		write(node->heredoc[1], input, ft_strlen(input));
		write(node->heredoc[1], "\n", 1);
	}
	exit(EXIT_SUCCESS);
}

void	create_heredocs(t_data *dat, t_exec *exec)
{
	t_cmdlst	*node;
	int			i;
	pid_t		pid;
	bool		doc_ready;

	node = exec->my_node;
	doc_ready = false;
	if (node->redirect == NULL)
		return ;
	while (node)
	{
		i = 0;
		while (node->redirect[i].name)
		{
			if (node->redirect[i].type == HEREDOC)
			{
				if (doc_ready == true)
					close(node->heredoc[0]);
				doc_ready = true;
				pipe(node->heredoc);
				pid = fork();
				if (pid == -1)
					exit(EXIT_FAILURE);
				if (pid == 0)
					run_heredoc(dat, exec, node, node->redirect[i].name);
				wait(NULL);
				close(node->heredoc[1]);
			}
			else if (node->redirect[i].type == REDIN && doc_ready == true)
			{
				doc_ready = false;
				close(node->heredoc[0]);
			}
			i++;
		}
		node = node->next;
	}
}

/*
	program flow notes:
	heredocs are generated and run before any other actions.
	Any error involving redirects prevents the associated command from running
*/
void	executor(t_data *dat)
{
	t_exec	exec;

	signals_in_process();
	if (*(dat->cmd_lst) == NULL)
		return ;
	exec.exit_code = dat->exit_code;
	exec.fork_num = count_forks(dat->cmd_lst);
	exec.my_node = *(dat->cmd_lst);
	create_heredocs(dat, &exec);
	if (check_builtin(dat, exec.my_node) && exec.fork_num == 1)
	{
		exec_parent_wrapper(dat, &exec);
		return ;
	}
	else
		exec_child_wrapper(dat, &exec);
}
