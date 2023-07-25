/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_table2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 14:45:24 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/25 14:45:24 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_cmd	*cmdlst_new_node(void);
char	**get_cmd_args(t_token *t_lst);
void	cmdlst_add_back(t_cmd **cmd_lst_head, t_cmd *new_node);

void	parse_non_command(t_token *token, t_cmd **cmd_lst_head, enum e_cmd_type type)
{
	t_cmd	*new_node;

	new_node = cmdlst_new_node();
	new_node->type = type;
	new_node->argv = (char **)malloc(sizeof(char *) * 2);
	new_node->argv[0] = token->token;
	new_node->argv[1] = NULL;
	cmdlst_add_back(cmd_lst_head, new_node);
	while (token && (token->type != TOK_PIPE || token->type != TOK_REDIN \
	|| token->type != TOK_REDOUT || token->type != TOK_REDAPPEND \
	|| token->type != TOK_HEREDOC))
	{
		token = token->next;
	}
}

void	parse_command(t_token *token, t_cmd **cmd_lst_head, enum e_cmd_type type)
{
	t_cmd	*new_node;

	new_node = cmdlst_new_node();
	new_node->argv = get_cmd_args(token);
	new_node->type = type;
	cmdlst_add_back(cmd_lst_head, new_node);
	while (token && (token->type != TOK_PIPE || token->type != TOK_REDIN \
	|| token->type != TOK_REDOUT || token->type != TOK_REDAPPEND \
	|| token->type != TOK_HEREDOC))
	{
		token = token->next;
	}
}

void	create_cmd_lst(t_data *data, t_cmd **cmd_lst_head)
{
	t_token			*current_token;
	enum e_cmd_type	type;

	type = FIRST;
	while (current_token)
	{
		while (current_token && current_token == TOK_SPACE)
			current_token = current_token->next;
		if (!current_token)
			break ;
		if (current_token->type == TOK_REDIN || current_token->type == TOK_REDOUT \
		|| current_token->type == TOK_REDAPPEND || current_token->type == TOK_HEREDOC)
		{
			parse_non_command(current_token->next, cmd_lst_head, current_token->type);
		}
		else
		{
			parse_command(current_token, cmd_lst_head, type);
			type = PIPE;
		}
	}
}
