/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list_node_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 14:48:50 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/09 14:48:50 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdbool.h>

/**
 * @brief checks if the token contains an equal sign
 * @param token pointer to the token to check
 * @return true if the token contains an equal sign, else false
 */
static bool	is_equal_token(char *token)
{
	int	i;

	if (!ft_isalpha(token[0]))
		return (false);
	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
			break ;
		i++;
	}
	if (token[i] != '=')
		return (false);
	i--;
	while (i >= 0)
	{
		if (!ft_isalnum(token[i]) && token[i] != '_')
			return (false);
		i--;
	}
	return (true);
}

/**
 * @brief gets the type of the token
 * @param token pointer to the token to check
 * @return type of the token
 */
enum e_token_type	get_token_type(char *token)
{
	if (token[0] == TOK_DQUOTE || token[0] == TOK_SQUOTE || \
	token[0] == TOK_PIPE || token[0] == TOK_DOLLAR || token[0] == TOK_SPACE)
		return ((enum e_token_type)token[0]);
	else if (token[0] == TOK_REDIN)
	{
		if (token[1] == TOK_REDIN)
			return (TOK_HEREDOC);
		else
			return (TOK_REDIN);
	}
	else if (token[0] == TOK_REDOUT)
	{
		if (token[1] == TOK_REDOUT)
			return (TOK_REDAPPEND);
		else
			return (TOK_REDOUT);
	}
	else if (is_equal_token(token))
		return (TOK_EQUAL);
	else if (ft_iswhitespace(token[0]))
		return (TOK_SPACE);
	else
		return (TOK_NAME);
}
