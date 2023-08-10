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

void	handle_single_quote(t_toklst **token, enum e_state_space space_state)
{
	trim_quotes(token, TOK_NAME, "\'");
	if (space_state == NOSPACE)
		quote_join(token, true);
	if ((*token)->next && (*token)->next->type != TOK_SPACE && \
	(*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE)
		quote_join(token, false);
}

void	handle_double_quote(t_toklst **token, enum e_state_space space_state)
{
	trim_quotes(token, TOK_DQUOTE, "\"");
	if (check_for_dollar((*token)->token))
	{
		// expansion(token);
		ft_printf("\033[31;1m\"expansion\"\033[0m needed for: %s\n", (*token)->token);
	}
	if (space_state == NOSPACE)
		quote_join(token, true);
	if ((*token)->next && (*token)->next->type != TOK_SPACE \
	&& (*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE \
	&& (*token)->next->type != TOK_DOLLAR)
		quote_join(token, false);
}

void	handle_quotes(t_toklst **token)
{
	enum e_state_space	space_state;

	if ((*token)->prev && (*token)->prev->type == TOK_SPACE)
		space_state = SPACE;
	else if ((*token)->prev)
		space_state = NOSPACE;
	else
		space_state = FIRST;
	if ((*token)->type == TOK_SQUOTE)
		handle_single_quote(token, space_state);
	else if ((*token)->type == TOK_DQUOTE)
		handle_double_quote(token, space_state);
}

// void	quotes(t_data *data)
// {
// 	t_toklst	*tmp;

// 	tmp = *(data->t_lst);
// 	while (tmp)
// 	{
// 		if (tmp->type == TOK_DQUOTE || tmp->type == TOK_SQUOTE)
// 			handle_quotes(&tmp);
// 		else if (tmp->type == TOK_DOLLAR)
// 		{
// 			expansion(&tmp);
// 			handle_quotes(&tmp);
// 			if (!tmp->prev)
// 				data->t_lst = &tmp;
// 		}
// 		tmp = tmp->next;
// 	}
// }

void	quotes(t_data *data, t_toklst **t_lst_head)
{
	t_toklst	*tmp;

	tmp = *t_lst_head;
	while (tmp)
	{
		if (tmp->type == TOK_DQUOTE || tmp->type == TOK_SQUOTE)
			handle_quotes(&tmp);
		else if (tmp->type == TOK_DOLLAR)
		{
			expansion(data, &tmp);
			handle_quotes(&tmp);
			if (!tmp->prev)
				*t_lst_head = tmp;
		}
		tmp = tmp->next;
	}
}
