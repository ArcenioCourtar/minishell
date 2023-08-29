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

static void	trim_quotes(t_data *data, t_toklst **token, enum e_token_type type, \
																	char *trim)
{
	char	*tmp;

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

static void	handle_single_quote(t_data *data, t_toklst **token, \
													enum e_st_space st_space)
{
	trim_quotes(data, token, TOK_NAME, "\'");
	if (st_space == NOSPACE)
		quote_join(data, token, true);
	if ((*token)->next && (*token)->next->type != TOK_SPACE && \
	(*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE)
		quote_join(data, token, false);
}

static void	handle_double_quote(t_data *data, t_toklst **token, \
													enum e_st_space st_space)
{
	trim_quotes(data, token, TOK_DQUOTE, "\"");
	if (check_for_dollar((*token)->token))
		expansion(data, token);
	if (st_space == NOSPACE)
		quote_join(data, token, true);
	if ((*token)->next && (*token)->next->type != TOK_SPACE \
	&& (*token)->next->type != TOK_SQUOTE && (*token)->next->type != TOK_DQUOTE \
	&& (*token)->next->type != TOK_DOLLAR)
		quote_join(data, token, false);
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
		handle_single_quote(data, token, st_space);
	else if ((*token)->type == TOK_DQUOTE)
		handle_double_quote(data, token, st_space);
}
