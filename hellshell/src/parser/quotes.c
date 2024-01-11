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

/**
 * @brief trims the quotes from the token
 * @param data pointer to the program data struct
 * @param token pointer to the token to trim
 * @param type type of quote to trim
 */
void	trim_quotes(t_data *data, t_toklst **token, enum e_token_type type)
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

/**
 * @brief checks if the token contains a dollar sign
 * @param data pointer to the program data struct
 * @param token pointer to the token to check
 * @return true if the token contains a dollar sign, else false
 */
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

/**
 * @brief checks if the token should be joined to the previous token
 * @param token pointer to the token to check
 * @return true if the token should be joined to the previous token, else false
 */
static bool	valid_join_front(t_toklst *token)
{
	if (!token->next)
		return (false);
	if (token->next->type == TOK_SPACE \
	|| token->next->type == TOK_SQUOTE \
	|| token->next->type == TOK_DQUOTE)
		return (false);
	if (token->next->type == TOK_DOLLAR && token->next->next)
		return (false);
	return (true);
}

/**
 * @brief modifies the token depending on the type of quote
 * @param data pointer to the program data struct
 * @param token pointer to the token to modify
 * @param type type of quote to modify
 * @param st_space type of space before the token
 */
static int	modify_quote_token(t_data *data, t_toklst **token, \
							enum e_token_type type, enum e_st_space st_space)
{
	trim_quotes(data, token, type);
	if (!(*token)->token[0] && (*token)->prev && (*token)->next)
	{
		handle_empty_quotes(data, token);
		return (1);
	}
	if (type == TOK_DQUOTE)
	{
		if (check_for_dollar((*token)->token))
			expansion(data, token);
	}
	if (st_space == NOSPACE)
		quote_join(data, token, true);
	if (valid_join_front(*token))
	{
		quote_join(data, token, false);
		if ((*token)->prev)
			*token = (*token)->prev;
	}
	return (0);
}

/**
 * @brief handles quotes accordingly
 * @param data pointer to the program data struct
 * @param token pointer to the token to handle
 */
int	handle_quotes(t_data *data, t_toklst **token)
{
	enum e_st_space	st_space;

	if ((*token)->prev && (*token)->prev->type == TOK_SPACE)
		st_space = SPAEC;
	else if ((*token)->prev && !is_redirect((*token)->prev->type) \
								&& (*token)->prev->type != TOK_PIPE)
		st_space = NOSPACE;
	else
		st_space = FIRST;
	return (modify_quote_token(data, token, (*token)->type, st_space));
}
