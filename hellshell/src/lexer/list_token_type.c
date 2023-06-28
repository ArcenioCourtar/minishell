/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_token_type.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 16:07:20 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/28 16:07:20 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

static int	is_equal_token(char *token)
{
	int	i;

	if (!ft_isalpha(token[0]))
		return (0);
	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
			break ;
		i++;
	}
	if (token[i] != '=')
		return (0);
	i--;
	while (i >= 0)
	{
		if (!ft_isalnum(token[i]) && token[i] != '_')
			return (0);
		i--;
	}
	return (1);
}

enum e_token_types	get_token_type(char *token)
{
	if (token[0] == TOK_DQUOTE || token[0] == TOK_SQUOTE || \
	token[0] == TOK_PIPE || token[0] == TOK_DOLLAR || token[0] == TOK_SPACE)
		return ((enum e_token_types)token[0]);
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
	else
		return (TOK_NAME);
}
