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

char	*heredoc_expansion(t_data *data, char *to_expand)
{
	int		i;
	char	**expansions;
	int		dol_count;
	char	*expansion;

	dol_count = count_dollar_signs(to_expand);
	if (dol_count == 0)
		return (NULL);
	expansions = (char **)malloc(sizeof(char *) * (dol_count + 1));
	if (!expansions)
		ft_error(errno, strerror(errno));
	i = 0;
	while (i < dol_count)
	{
		expansions[i] = get_expansion(data, to_expand, i, dol_count);
		i++;
	}
	expansions[i] = "\0";
	expansion = NULL;
	expansion = add_expans_to_token(to_expand, expansions);
	free(expansions);
	return (expansion);
}

void	run_heredoc(t_data *dat, t_cmdlst *node, char *delim, \
enum e_redir_type type)
{
	char	*input;
	char	*expanded;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			printf("heredoc delimited by EOF\n");
			break ;
		}
		if (ft_strlen(delim) == 0 && ft_strlen(input) == 0)
			break ;
		if (ft_strncmp(delim, input, ft_strlen(delim) + 1) == 0)
			break ;
		if (type == HEREDOC_EXP && count_dollar_signs(input) > 0)
		{
			expanded = heredoc_expansion(dat, input);
			write(node->heredoc[1], expanded, ft_strlen(expanded));
			free(expanded);
		}
		else
			write(node->heredoc[1], input, ft_strlen(input));
		write(node->heredoc[1], "\n", 1);
		free(input);
	}
	exit(EXIT_SUCCESS);
}

static void	hd_create(t_data *dat, t_cmdlst *node, int i, t_cmdlst **doc_ready)
{
	pid_t		pid;

	if (node->redirect[i].type == HEREDOC_EXP || \
	node->redirect[i].type == HEREDOC_NOEXP)
	{
		if (*doc_ready)
			close(node->heredoc[0]);
		*doc_ready = node;
		if (pipe(node->heredoc) == -1)
		{
			ft_printf_err("Broken pipe\n");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			run_heredoc(dat, node, node->redirect[i].name, \
			node->redirect[i].type);
		close(node->heredoc[1]);
		wait(NULL);
	}
	else if ((node->redirect[i].type == REDIN && *doc_ready))
	{
		*doc_ready = NULL;
		close(node->heredoc[0]);
	}
}

void	create_heredocs(t_data *dat, t_exec *exec)
{
	int			i;
	t_cmdlst	*doc_ready;
	t_cmdlst	*node;

	node = exec->my_node;
	while (node)
	{
		i = 0;
		doc_ready = NULL;
		while (node->redirect && node->redirect[i].name)
		{
			if (g_signal == SIGINT)
				break ;
			hd_create(dat, node, i, &doc_ready);
			if (node->argv[0] == NULL && doc_ready)
			{
				doc_ready = NULL;
				close(node->heredoc[0]);
			}
			i++;
		}
		if (doc_ready)
			doc_ready->hd_used = true;
		node = node->next;
	}
}
