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

#include "minishell.h"
#include "lexer.h"
#include "libft.h"

// iterates over [str] with [i]
// to check if quote [type] is closed
// returns 1 for unclosed quotes
// returns 0 for closed quotes
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

// iterates over [str] with [i]
// to check for repeated (returns 124) or empty (returns 1) pipes
// returns 0 for no errors
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

// checks for syntax errors in [input_str] regarding pipes and quotes
// returns 39(') or 34(") in case of unclosed quotes
// returns 124 or 1 in case of error regarding '|'
// returns 0 on succes
static int	pipe_quote_check(char *input_str)
{
	int	i;
	int	errnum;

	i = 0;
	while (input_str[i] && ft_iswhitespace(input_str[i]))
		i++;
	if (input_str[i] == TOK_PIPE)
		return (TOK_PIPE);
	while (input_str[i])
	{
		if (input_str[i] == TOK_SQUOTE \
			&& iter_quoted_str(input_str, TOK_SQUOTE, &i))
			return (TOK_SQUOTE);
		else if (input_str[i] == TOK_DQUOTE \
			&& iter_quoted_str(input_str, TOK_DQUOTE, &i))
			return (TOK_DQUOTE);
		else if (input_str[i] == TOK_PIPE)
		{
			errnum = iter_pipe_str(input_str, &i);
			if (errnum)
				return (errnum);
		}
		i++;
	}
	return (0);
}

// returns error number for corresponding syntax error
// regarding pipes and quotes
// and prints corresponding error message
int	syntax_error_checks(t_data *data)
{
	int	errnumber;

	errnumber = pipe_quote_check(data->input);
	if (errnumber == TOK_PIPE)
		ft_printf_err("hellshell: syntax error \
										near unexpected token `|'\n");
	else if (errnumber)
		ft_printf_err("hellshell: syntax error \
										near unexpected token `newline'\n");
	else if (errnumber == TOK_DQUOTE || errnumber == TOK_SQUOTE)
		ft_printf_err("minishell: syntax error: \
										unclosed %c\n", errnumber);
	return (errnumber);
}

// prints error message corresponding to a redirect error in [token]
void	print_redirect_error(t_toklst *token)
{
	if (token)
		ft_printf_err("hellshell: syntax error \
								near unexpected token `%s'\n", token->token);
	else
		ft_printf_err("hellshell: syntax error \
								near unexpected token `newline'\n");
}
