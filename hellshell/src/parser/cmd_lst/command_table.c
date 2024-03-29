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

/**
 * @brief parses a chunk of tokens into a command list node
 * @param token pointer to the first token of the command
 * @param cmd_lst_head pointer to the head of the command list
 * @param type type of the command
 * @return 0 for no errors, 1 for syntax errors
 */
static int	parse_chunk(t_toklst *token, t_cmdlst **cmd_lst_head, \
														enum e_cmd_type type)
{
	t_cmdlst	*new_node;
	int			ret_value;

	ret_value = 0;
	new_node = cmdlst_new_node();
	cmdlst_add_back(cmd_lst_head, new_node);
	new_node->type = type;
	ret_value = redirects_to_node(token, new_node);
	if (ret_value)
		return (ret_value);
	argv_to_node(token, new_node);
	return (ret_value);
}

/**
 * @brief iterates over the token to find the next command
 * @param token pointer to the first token of the command
 * @return 1 if there are no more commands, 0 otherwise
 */
static int	iterate_token(t_toklst **token)
{
	if (!*token)
		return (1);
	if ((*token)->type == TOK_PIPE)
		*token = (*token)->next;
	while (*token && (*token)->type == TOK_SPACE)
		*token = (*token)->next;
	if (!*token)
		return (1);
	return (0);
}

/**
 * @brief creates the command list
 * @param data pointer to the program data struct
 * @return 0 for no errors, 1 for syntax errors
 */
int	create_cmd_lst(t_data *data)
{
	t_toklst		*current_token;
	enum e_cmd_type	type;
	int				ret_value;

	ret_value = 0;
	type = CMD_FIRST;
	current_token = *(data->t_lst);
	while (current_token)
	{
		if (current_token->type == TOK_INVALID)
		{
			token_lstdel_node(&current_token);
			*(data->t_lst) = current_token;
		}
		if (iterate_token(&current_token))
			break ;
		ret_value = parse_chunk(current_token, data->cmd_lst, type);
		if (ret_value)
			break ;
		type = CMD_PIPE;
		while (current_token && current_token->type != TOK_PIPE)
			current_token = current_token->next;
	}
	token_lstfree(data->t_lst);
	return (ret_value);
}
