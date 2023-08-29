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
		return (1);
	(*i)--;
	return (0);
}

//returns "/' value in case of unclosed "/', 0 on succes
static int	pipe_quote_check(t_data data)
{
	int	i;

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
		else if (data.input[i] == TOK_PIPE && iter_pipe_str(data.input, &i))
			return (TOK_PIPE);
		i++;
	}
	return (0);
}

int	syntax_error_checks(t_data *data)
{
	int	errnumber;

	errnumber = pipe_quote_check(*data);
	if (errnumber == TOK_PIPE)
		ft_printf("hellshell: syntax error near unexpected token `|'\n");
	else if (errnumber)
		ft_printf("minishell: syntax error: unclosed %c\n", errnumber);
	return (errnumber);
}

void	print_redirect_error(t_toklst *token)
{
	if (token)
		ft_printf("hellshell: syntax error near unexpected token `%s'\n", \
																token->token);
	else
		ft_printf("hellshell: syntax error near unexpected token `newline'\n");
}
