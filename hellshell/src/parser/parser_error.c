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

/**
 * @brief iterates over a string to check if a quote is closed
 * @param str string to iterate over
 * @param type type of quote to check
 * @param i pointer to the index of the string
 */
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

/**
 * @brief iterates over a string to check for repeated or empty pipes
 * @param str string to iterate over
 * @param i pointer to the index of the string
 * @return 0 for no errors, 124 for repeated pipes, 1 for empty pipes
 */
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

/**
 * @brief checks for syntax errors in a string regarding pipes and quotes
 * @param input_str string to check
 * @return 39(') or 34(") in case of unclosed quotes, 
 * 124 for repeated pipes or 1 for empty pipes, 0 on succes
 */
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
/**
 * @brief prints error message corresponding to a syntax error
 * @param data pointer to the program data struct
 * @return 39(') or 34(") in case of unclosed quotes, 
 * 124 for repeated pipes or 1 for empty pipes, 0 on succes
 */
int	syntax_error_checks(t_data *data)
{
	int	errnumber;

	errnumber = pipe_quote_check(data->input);
	if (errnumber == TOK_PIPE)
		ft_printf_err("hellshell: %s `|'\n", UNEXP_TOK_ERROR);
	else if (errnumber)
		ft_printf_err("hellshell: %s `newline'\n", UNEXP_TOK_ERROR);
	else if (errnumber == TOK_DQUOTE || errnumber == TOK_SQUOTE)
		ft_printf_err("minishell: syntax error: unclosed %c\n", errnumber);
	return (errnumber);
}

/**
 * @brief prints error message corresponding to a redirect error in a token
 * @param token token where error occured (NULL if newline)
 */
void	print_redirect_error(t_toklst *token)
{
	if (token)
		ft_printf_err("hellshell: %s `%s'\n", UNEXP_TOK_ERROR, token->token);
	else
		ft_printf_err("hellshell: %s `newline'\n", UNEXP_TOK_ERROR);
}
