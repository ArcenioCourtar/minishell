/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_table3.c                                   :+:    :+:            */
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

t_cmd	*cmdlst_new_node(void);
char	**get_cmd_args(t_token *t_lst);
void	cmdlst_add_back(t_cmd **cmd_lst_head, t_cmd *new_node);

int	count_redirs(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp && tmp->type != TOK_PIPE)
	{
		if (tmp->type == TOK_REDIN || tmp->type == TOK_REDOUT \
		|| tmp->type == TOK_REDAPPEND || tmp->type == TOK_HEREDOC)
		{
			count++;
			tmp = tmp->next;
			while (tmp && tmp->type == TOK_SPACE)
				tmp = tmp->next;
			if (!tmp)
				break ;
			// tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (count);
}

void	parse_redirect(t_token *token, t_cmd *node, int r)
{
	node->redirect[r].type = (enum e_redir_type)token->type;
	token = token->next;
	while (token && token->type == TOK_SPACE)
		token = token->next;
	node->redirect[r].name = token->token;
	token = token->next;
}

void	redirects_to_node(t_token *token, t_cmd *node)
{
	int		redir_count;
	int		r;
	t_token	*tmp;

	tmp = token;
	redir_count = count_redirs(tmp);
	node->redirect = (t_redirect *)malloc(sizeof(t_redirect) * \
	(redir_count + 1));
	r = 0;
	while (r < redir_count)
	{
		while (tmp->type != TOK_REDIN && tmp->type != TOK_REDOUT \
		&& tmp->type != TOK_REDAPPEND && tmp->type != TOK_HEREDOC)
			tmp = tmp->next;
		node->redirect[r].type = (enum e_redir_type)tmp->type;
		tmp = tmp->next;
		while (tmp && tmp->type == TOK_SPACE)
			tmp = tmp->next;
		if (tmp)
			node->redirect[r].name = tmp->token;
		else
			node->redirect[r].name = NULL;
		ft_printf("[%i]\t%i\t%s\n", r, node->redirect[r].type, node->redirect[r].name);
		r++;
	}
}

void	parse_chunk(t_token *token, t_cmd **cmd_lst_head, enum e_cmd_type type)
{
	t_cmd	*new_node;

	new_node = cmdlst_new_node();
	new_node->type = type;
	redirects_to_node(token, new_node);
	exit(1);
	cmdlst_add_back(cmd_lst_head, new_node);
}

void	create_cmd_lst2(t_data *data, t_cmd **cmd_lst_head)
{
	t_token	*current_token;
	enum e_cmd_type	type;

	type = CMD_FIRST;
	current_token = *(data->t_lst);
	while (current_token)
	{
		while (current_token && current_token->type == TOK_SPACE)
			current_token = current_token->next;
		if (!current_token)
			break ;
		parse_chunk(current_token, cmd_lst_head, type);
		type = CMD_PIPE;
		while (current_token && current_token->type != TOK_PIPE)
			current_token = current_token->next;
	}
}
