/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 12:24:16 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/03 12:24:16 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"

/**
 * @brief checks if a token contains a dollar sign
 * @param token pointer to the token to check
 * @return true if the token contains a dollar sign, else false
 */
bool	check_for_dollar(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == TOK_DOLLAR && token[i + 1] && token[i + 1] != ' ')
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Handles a token accordingly depending on type or place in list
 * @param data pointer to the program data struct
 * @param token pointer to the token to expand
 */
static void	expansion_wrapper(t_data *data, t_toklst **token)
{
	if (!(*token)->next || (*token)->next->type == TOK_SPACE)
	{
		(*token)->type = TOK_NAME;
		*token = (*token)->next;
	}
	else if ((*token)->next->type == TOK_DQUOTE \
				|| (*token)->next->type == TOK_SQUOTE)
		token_lstdel_node(token);
	else
	{
		(*token)->next->token = getvar(data, (*token)->next->token, false);
		token_lstdel_node(token);
		if (ft_strlen((*token)->token) == 0)
			(*token)->type = TOK_INVALID;
		else
		{
			if (check_for_spaces((*token)->token))
				split_expansion(data, token);
			if ((*token) && (*token)->prev && (*token)->prev->type != TOK_SPACE \
			&& !is_redirect((*token)->prev->type))
				quote_join(data, token, true);
		}
	}
}

/**
 * @brief expands the variable in a token
 * @param data pointer to the program data struct
 * @param token pointer to the token to expand
 */
void	expansion(t_data *data, t_toklst **token)
{
	if (heredoc_exception(data, token))
		return ;
	if ((*token)->type == TOK_DQUOTE)
		expand_in_quotes(data, *token);
	else if ((*token)->type == TOK_DOLLAR)
		expansion_wrapper(data, token);
}
