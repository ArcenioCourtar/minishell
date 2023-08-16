/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 15:34:18 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/01 15:34:18 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

void	handle_single_quote(t_toklst **token, enum e_st_space st_space)
{
	trim_quotes(token, TOK_NAME, "\'");
	if (st_space == NOSPACE)
		quote_join(token, true);
	if ((*token)->next && (*token)->next->type != TOK_SPACE && \
	(*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE)
		quote_join(token, false);
}

void	handle_double_quote(t_data *data, t_toklst **token, \
													enum e_st_space st_space)
{
	trim_quotes(token, TOK_DQUOTE, "\"");
	if (check_for_dollar((*token)->token))
		expansion(data, token);
	if (st_space == NOSPACE)
		quote_join(token, true);
	if ((*token)->next && (*token)->next->type != TOK_SPACE \
	&& (*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE \
	&& (*token)->next->type != TOK_DOLLAR)
		quote_join(token, false);
}

void	handle_quotes(t_data *data, t_toklst **token)
{
	enum e_st_space	st_space;

	if ((*token)->prev && (*token)->prev->type == TOK_SPACE)
		st_space = SPACE;
	else if ((*token)->prev)
		st_space = NOSPACE;
	else
		st_space = FIRST;
	if ((*token)->type == TOK_SQUOTE)
		handle_single_quote(token, st_space);
	else if ((*token)->type == TOK_DQUOTE)
		handle_double_quote(data, token, st_space);
}

void	quotes(t_data *data, t_toklst **t_lst_head)
{
	t_toklst	*tmp;

	tmp = *t_lst_head;
	while (tmp)
	{
		if (tmp->type == TOK_DQUOTE || tmp->type == TOK_SQUOTE)
			handle_quotes(data, &tmp);
		else if (tmp->type == TOK_DOLLAR)
		{
			expansion(data, &tmp);
			handle_quotes(data, &tmp);
			if (!tmp->prev)
				*t_lst_head = tmp;
		}
		tmp = tmp->next;
	}
}
