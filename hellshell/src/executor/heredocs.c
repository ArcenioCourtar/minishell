/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/29 19:34:12 by acourtar      #+#    #+#                 */
/*   Updated: 2023/11/29 19:34:12 by acourtar      ########   odam.nl         */
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

void	run_heredoc(t_data *dat, t_cmdlst *node, char *delim, \
enum e_redir_type type)
{
	char	*input;

	(void) dat;
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strlen(delim) == 0 && ft_strlen(input) == 0)
			break ;
		if (ft_strncmp(delim, input, ft_strlen(delim) + 1) == 0)
			break ;
		if (type == HEREDOC_EXP)
			ft_printf_err("expansion code here\n");
		write(node->heredoc[1], input, ft_strlen(input));
		write(node->heredoc[1], "\n", 1);
		free(input);
	}
	exit(EXIT_SUCCESS);
}

static void	hd_create(t_data *dat, t_cmdlst *node, int i, bool *doc_ready)
{
	pid_t		pid;

	if (node->redirect[i].type == HEREDOC_EXP || \
	node->redirect[i].type == HEREDOC_NOEXP)
	{
		if (*doc_ready == true)
			close(node->heredoc[0]);
		*doc_ready = true;
		if (pipe(node->heredoc) == -1)
			ft_printf_err("Broken pipe\n");
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			run_heredoc(dat, node, node->redirect[i].name, \
			node->redirect[i].type);
		wait(NULL);
		close(node->heredoc[1]);
	}
	else if ((node->redirect[i].type == REDIN && *doc_ready == true))
	{
		*doc_ready = false;
		close(node->heredoc[0]);
	}
}

static void	hd_loop(t_data *dat, t_exec *exec)
{
	int			i;
	bool		doc_ready;
	t_cmdlst	*node;

	node = exec->my_node;
	while (node)
	{
		i = 0;
		doc_ready = false;
		while (node->redirect[i].name)
		{
			hd_create(dat, node, i, &doc_ready);
			if (node->argv[0] == NULL)
				close(node->heredoc[0]);
			i++;
		}
		node = node->next;
	}
}

void	create_heredocs(t_data *dat, t_exec *exec)
{
	if (exec->my_node->redirect == NULL)
		return ;
	hd_loop(dat, exec);
}
