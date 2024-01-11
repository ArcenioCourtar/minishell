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

static void	parser_wrapper(t_toklst *tmp, t_data *data)
{
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
			{	
				if (!handle_quotes(data, &tmp))
					tmp = tmp->next;
			}
			else
				tmp = tmp->next;
		}
	}
}

/**
 * @brief checks for syntax errors, handles expansions and quotes and creates
 * the command list
 * @param data pointer to the data struct
 * @return 0 for no errors, 1 for syntax errors
 */
int	parser(t_data *data)
{
	t_toklst	*tmp;

	if (syntax_error_checks(data))
	{
		token_lstfree(data->t_lst);
		return (ERR_SYNTAX);
	}
	tmp = *(data->t_lst);
	parser_wrapper(tmp, data);
	return (create_cmd_lst(data));
}
