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

static void	parse_chunk(t_toklst *token, t_cmdlst **cmd_lst_head, \
											enum e_cmd_type type)
{
	t_cmdlst	*new_node;

	new_node = cmdlst_new_node();
	new_node->type = type;
	redirects_to_node(token, new_node);
	argv_to_node(token, new_node);
	cmdlst_add_back(cmd_lst_head, new_node);
}

void	create_cmd_lst(t_data *data)
{
	t_toklst		*current_token;
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
		parse_chunk(current_token, data->cmd_lst, type);
		type = CMD_PIPE;
		while (current_token && current_token->type != TOK_PIPE)
			current_token = current_token->next;
	}
	token_lstfree(data->t_lst);
	printf_cmd_table(data->cmd_lst);
}
