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
#include "lexer.h"
#include "libft.h"

static void	trim_quotes(t_data *data, t_toklst **token, enum e_token_type type)
{
	char	*tmp;
	char	trim[2];

	trim[0] = (char)type;
	trim[1] = '\0';
	tmp = ft_strtrim((*token)->token, trim);
	add_to_free_lst(data, tmp);
	(*token)->token = tmp;
	(*token)->type = type;
}

void	quote_join(t_data *data, t_toklst **token, bool joinaddback)
{
	if (!*token)
		return ;
	if (joinaddback)
	{
		(*token)->prev->token = ft_strjoin((*token)->prev->token, \
														(*token)->token);
		add_to_free_lst(data, (*token)->prev->token);
	}
	else
	{
		(*token)->token = ft_strjoin((*token)->token, \
													(*token)->next->token);
		add_to_free_lst(data, (*token)->token);
		*token = (*token)->next;
	}
	token_lstdel_node(token);
}

static void	handle_empty_quotes(t_data *data, t_toklst **token)
{
	if ((*token)->next->type == TOK_NAME)
	{
		(*token)->prev->token = ft_strjoin((*token)->prev->token, \
													(*token)->next->token);
		add_to_free_lst(data, (*token)->prev->token);
		token_lstdel_node(token);
		token_lstdel_node(token);
	}
	else
	{
		token_lstdel_node(token);
		if ((*token)->prev)
			*token = (*token)->prev;
	}
}

static void	modify_quote_token(t_data *data, t_toklst **token, \
							enum e_token_type type, enum e_st_space st_space)
{
	trim_quotes(data, token, type);
	if (!(*token)->token[0] && (*token)->prev && (*token)->next)
	{
		handle_empty_quotes(data, token);
		return ;
	}
	if (type == TOK_DQUOTE)
	{
		if (check_for_dollar((*token)->token))
			expansion(data, token);
	}
	if (st_space == NOSPACE)
	{
		quote_join(data, token, true);
		if ((*token)->prev)
			*token = (*token)->prev;
	}
	else if ((*token)->next && (*token)->next->type != TOK_SPACE && \
	(*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE \
	&& (*token)->next->type != TOK_DOLLAR)
	{
		quote_join(data, token, false);
		if ((*token)->prev)
			*token = (*token)->prev;
	}
}

void	handle_quotes(t_data *data, t_toklst **token)
{
	enum e_st_space	st_space;

	if ((*token)->prev && (*token)->prev->type == TOK_SPACE)
		st_space = SPACE;
	else if ((*token)->prev && !is_redirect((*token)->prev->type) \
								&& (*token)->prev->type != TOK_PIPE)
		st_space = NOSPACE;
	else
		st_space = FIRST;
	modify_quote_token(data, token, (*token)->type, st_space);
}
