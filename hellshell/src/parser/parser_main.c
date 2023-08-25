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

#include "parser.h"
#include "minishell.h"
#include "libft.h"

/** PARSING ORDER
 * quotes
 * heredoc
 * pipes i guess
 * expanding
 * put everything together
 */

/** QUOTES
 * state SPACE or NOSPACE before quote
 * if SPACE
 * 		in state S/D QUOTE 
 * 				something
 * if NOSPACE
 * 		in state S/D QUOTE
 * 				append to what's before
 * 				delete quotes token from list
 */

void	parser(t_data *data)
{
	t_toklst	*tmp;

	syntax_error_checks(data);
	tmp = *(data->t_lst);
	while (tmp)
	{
		if (tmp->type == TOK_DQUOTE || tmp->type == TOK_SQUOTE)
			handle_quotes(data, &tmp);
		else if (tmp->type == TOK_DOLLAR)
		{
			expansion(data, &tmp);
			if (!tmp->prev)
				*(data->t_lst) = tmp;
		}
		tmp = tmp->next;
	}
	create_cmd_lst(data);
}
