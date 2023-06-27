/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 15:58:15 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/26 15:58:15 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_lexer_lst
{
	char				*token;
	int					type;
	struct s_lexer_lst	*next;
}	t_lexer_lst;

/*	delimiters
	' " $ < << > >> | <space>	
*/

enum e_token {
	TOK_DQUOTE = '"',
	TOK_SQUOTE = '\'',
	TOK_NAME = 'a',
	TOK_PIPE = '|',
	TOK_DOLLAR = '$',
	TOK_REDIN = '<',
	TOK_REDOUT = '>',
	TOK_HEREDOC = '<' * 2,
	TOK_REDAPPEND = '>' * 2
};

#endif