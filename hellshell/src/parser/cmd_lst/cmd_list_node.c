/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_list_node.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/07 11:55:29 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/07 11:55:29 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"
#include "exit_codes.h"

/**
 * @brief assigns the name of a redirection to a command list node
 * @param token pointer to the first token of the command
 * @param node pointer to the command list node
 * @param i index of the redirection
 */
static int	assign_redirect_name(t_toklst *token, t_cmdlst *node, int i)
{
	while (token && token->type == TOK_SPACE)
		token = token->next;
	if (token && token->type == TOK_NAME)
		node->redirect[i].name = token->token;
	else if (token && (token->type == TOK_DQUOTE || token->type == TOK_SQUOTE))
	{
		node->redirect[i].name = token->token;
		if (node->redirect[i].type == HEREDOC_EXP)
			node->redirect[i].type = HEREDOC_NOEXP;
	}
	else
	{
		print_redirect_error(token);
		return (ERR_SYNTAX);
	}
	return (0);
}

/**
 * @brief loops over the redirections in a command and assigns them to a node
 * @param token pointer to the first token of the command
 * @param command pointer to the command list node
 * @param rdr_count number of redirections in the command
 * @return 0 for no errors, 1 for syntax errors
 */
static int	loop_redirs_to_node(t_toklst *token, t_cmdlst *command, \
																int rdr_count)
{
	int	i;
	int	ret_value;

	i = 0;
	ret_value = 0;
	while (i < rdr_count)
	{
		while (!is_redirect(token->type))
			token = token->next;
		command->redirect[i].type = (enum e_redir_type)token->type;
		token = token->next;
		ret_value = assign_redirect_name(token, command, i);
		if (ret_value)
			break ;
		i++;
	}
	return (ret_value);
}

/**
 * @brief assigns the redirections in a command to a command list node
 * @param token pointer to the first token of the command
 * @param node pointer to the command list node
 * @return 0 for no errors, 1 for syntax errors
 */
int	redirects_to_node(t_toklst *token, t_cmdlst *node)
{
	int	ret_value;
	int	rdr_count;

	ret_value = 0;
	rdr_count = count_redirs(token);
	if (!rdr_count)
		return (ret_value);
	node->redirect = (t_redirect *)malloc(sizeof(t_redirect) * (rdr_count + 1));
	if (!node->redirect)
		ft_error(errno, strerror(errno));
	ret_value = loop_redirs_to_node(token, node, rdr_count);
	node->redirect[rdr_count].name = NULL;
	return (ret_value);
}

/**
 * @brief loops over the arguments in a command and assigns them to a node
 * @param token pointer to the first token of the command
 * @param node pointer to the command list node
 */
void	argv_to_node(t_toklst *token, t_cmdlst *node)
{
	t_toklst	*tmp;
	int			argc;
	int			i;

	tmp = token;
	argc = argv_count(tmp);
	node->argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!node->argv)
		ft_error(errno, strerror(errno));
	i = 0;
	while (i < argc)
	{
		while (tmp && tmp->type == TOK_SPACE)
			tmp = tmp->next;
		if (is_redirect(tmp->type))
			skip_redirects(&tmp);
		if (tmp && tmp->type != TOK_SPACE && !is_redirect(tmp->type))
		{
			node->argv[i] = tmp->token;
			i++;
			tmp = tmp->next;
		}
	}
	node->argv[argc] = NULL;
}
