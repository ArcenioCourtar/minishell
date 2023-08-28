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

static int	assign_redirect_name(t_toklst *token, t_cmdlst *node, int i)
{
	while (token && token->type == TOK_SPACE)
		token = token->next;
	if (token && (token->type == TOK_DQUOTE || token->type == TOK_SQUOTE \
													|| token->type == TOK_NAME))
		node->redirect[i].name = token->token;
	else
	{
		print_redirect_error(token);
		return (ERR_SYNTAX);
	}
	return (0);
}

int	redirects_to_node(t_toklst *token, t_cmdlst *node)
{
	int			rdr_count;
	int			r;
	t_toklst	*tmp;
	int			ret_value;

	ret_value = 0;
	tmp = token;
	rdr_count = count_redirs(tmp);
	if (!rdr_count)
		return (ret_value);
	node->redirect = (t_redirect *)malloc(sizeof(t_redirect) * (rdr_count + 1));
	if (!node->redirect)
		ft_error(errno, strerror(errno));
	r = 0;
	while (r < rdr_count)
	{
		while (!is_redirect(tmp->type))
			tmp = tmp->next;
		node->redirect[r].type = (enum e_redir_type)tmp->type;
		tmp = tmp->next;
		ret_value = assign_redirect_name(tmp, node, r);
		if (ret_value)
			return (ret_value);
		r++;
	}
	node->redirect[rdr_count].name = NULL;
	return (ret_value);
}

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
