/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_table.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 17:26:55 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/25 17:26:55 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>

void	redirect_error(t_token *token);

void	redirects_to_node(t_token *token, t_cmd *node)
{
	int		rdr_count;
	int		r;
	t_token	*tmp;

	tmp = token;
	rdr_count = count_redirs(tmp);
	node->redirect = (t_redirect *)malloc(sizeof(t_redirect) * (rdr_count + 1));
	r = 0;
	while (r < rdr_count)
	{
		while (!is_redirect(tmp->type))
			tmp = tmp->next;
		node->redirect[r].type = (enum e_redir_type)tmp->type;
		tmp = tmp->next;
		while (tmp && tmp->type == TOK_SPACE)
			tmp = tmp->next;
		if (tmp && (tmp->type == TOK_DQUOTE || tmp->type == TOK_SQUOTE || \
		tmp->type == TOK_NAME))
			node->redirect[r].name = tmp->token;
		else
			redirect_error(tmp);
		r++;
	}
	node->redirect[rdr_count].name = NULL;
}

void	argv_to_node(t_token *token, t_cmd *node)
{
	t_token	*tmp;
	int		argc;
	int		i;

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

void	parse_chunk(t_token *token, t_cmd **cmd_lst_head, enum e_cmd_type type)
{
	t_cmd	*new_node;

	new_node = cmdlst_new_node();
	new_node->type = type;
	redirects_to_node(token, new_node);
	argv_to_node(token, new_node);
	cmdlst_add_back(cmd_lst_head, new_node);
}

void	create_cmd_lst(t_data *data, t_cmd **cmd_lst_head)
{
	t_token			*current_token;
	enum e_cmd_type	type;

	type = CMD_FIRST;
	current_token = *(data->t_lst);
	while (current_token)
	{
		if (current_token->type == TOK_PIPE)
			current_token = current_token->next;
		while (current_token && current_token->type == TOK_SPACE)
			current_token = current_token->next;
		if (!current_token)
			break ;
		parse_chunk(current_token, cmd_lst_head, type);
		type = CMD_PIPE;
		while (current_token && current_token->type != TOK_PIPE)
			current_token = current_token->next;
	}
	printf_cmd_table(cmd_lst_head);
}
