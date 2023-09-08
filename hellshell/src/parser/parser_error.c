/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/26 16:06:15 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/26 16:06:15 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "minishell.h"

static int	iter_quoted_str(char *str, enum e_token_type type, int *i)
{
	enum e_token_type	state;

	state = type;
	while (state == type)
	{
		(*i)++;
		if (!str[*i])
			return (1);
		if (str[*i] == (char)type)
			state = TOK_NAME;
	}
	return (0);
}

static int	iter_pipe_str(char *str, int *i)
{
	(*i)++;
	while (str[*i] && ft_iswhitespace(str[*i]))
		(*i)++;
	if (str[*i] == TOK_PIPE)
		return (TOK_PIPE);
	else if (!str[*i])
		return (1);
	(*i)--;
	return (0);
}

/** returns 39('), 34(") in case of unclosed quotes
 * 	returns 124, 1 in case of syntax error regarding '|'
 *	returns 0 on succes
*/
static int	pipe_quote_check(t_data data)
{
	int	i;
	int	errnum;

	i = 0;
	while (data.input[i] && ft_iswhitespace(data.input[i]))
		i++;
	if (data.input[i] == TOK_PIPE)
		return (TOK_PIPE);
	while (data.input[i])
	{
		if (data.input[i] == TOK_SQUOTE \
			&& iter_quoted_str(data.input, TOK_SQUOTE, &i))
			return (TOK_SQUOTE);
		else if (data.input[i] == TOK_DQUOTE \
			&& iter_quoted_str(data.input, TOK_DQUOTE, &i))
			return (TOK_DQUOTE);
		else if (data.input[i] == TOK_PIPE)
		{
			errnum = iter_pipe_str(data.input, &i);
			if (errnum)
				return (errnum);
		}
		i++;
	}
	return (0);
}

int	syntax_error_checks(t_data *data)
{
	int	errnumber;

	errnumber = pipe_quote_check(*data);
	if (errnumber == TOK_PIPE)
		printf("hellshell: syntax error near unexpected token `|'\n");
	else if (errnumber)
		printf("hellshell: syntax error near unexpected token `newline'\n");
	else if (errnumber == TOK_DQUOTE || errnumber == TOK_SQUOTE)
		printf("minishell: syntax error: unclosed %c\n", errnumber);
	return (errnumber);
}

void	print_redirect_error(t_toklst *token)
{
	if (token)
		printf("hellshell: syntax error near unexpected token `%s'\n", \
																token->token);
	else
		printf("hellshell: syntax error near unexpected token `newline'\n");
}
