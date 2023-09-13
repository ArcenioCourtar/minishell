/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 13:05:17 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/30 13:05:17 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "exit_codes.h"

int	parser(t_data *data)
{
	t_toklst	*tmp;

	if (syntax_error_checks(data))
	{
		token_lstfree(data->t_lst);
		return (ERR_SYNTAX);
	}
	tmp = *(data->t_lst);
	while (tmp)
	{
		if (tmp->type == TOK_DOLLAR)
		{
			expansion(data, &tmp);
			if (tmp && !tmp->prev)
				*(data->t_lst) = tmp;
		}
		else
		{
			if (tmp->type == TOK_DQUOTE || tmp->type == TOK_SQUOTE)
				handle_quotes(data, &tmp);
			tmp = tmp->next;
		}
	}
	return (create_cmd_lst(data));
}
