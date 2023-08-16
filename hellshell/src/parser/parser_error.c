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

void	redirect_error(t_toklst *token)
{
	if (token)
		ft_printf("hellshell: syntax error near unexpected token '%s'\n", \
																token->token);
	else
		ft_printf("hellshell: syntax error near unexpected token 'newline'\n");
	exit(258);
}

void	quotes_check(t_data data)
{
	int					i;
	enum e_token_type	state;

	i = 0;
	while (data.input[i])
	{
		if (data.input[i] == TOK_SQUOTE)
		{
			state = TOK_SQUOTE;
			while (state == TOK_SQUOTE)
			{
				i++;
				if (!data.input[i])
					ft_error(EIO, "minishell: syntax error: unclosed \'");
				if (data.input[i] == TOK_SQUOTE)
					state = TOK_NAME;
			}
		}
		else if (data.input[i] == TOK_DQUOTE)
		{
			state = TOK_DQUOTE;
			while (state == TOK_DQUOTE)
			{
				i++;
				if (!data.input[i])
					ft_error(EIO, "minishell: syntax error: unclosed \"");
				if (data.input[i] == TOK_DQUOTE)
					state = TOK_NAME;
			}
		}
		i++;
	}
}

/** SYNTAX ERRORS
 * '| test'
 * 'echo < >'
 * 'echo | |'
 * '<'
 */