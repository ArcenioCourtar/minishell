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

# include <errno.h>
# include <string.h>

enum e_delims {
	DEL_DQUOTE = '"',
	DEL_SQUOTE = '\'',
	DEL_PIPE = '|',
	DEL_DOLLAR = '$',
	DEL_REDIN = '<',
	DEL_REDOUT = '>',
	DEL_SPACE = ' '
};

enum e_token_types {
	TOK_DQUOTE = '"',
	TOK_SQUOTE = '\'',
	TOK_PIPE = '|',
	TOK_DOLLAR = '$',
	TOK_SPACE = ' ',
	TOK_REDIN = '<',
	TOK_REDOUT = '>',
	TOK_REDAPPEND = '>' / 2,
	TOK_HEREDOC = '<' / 2,
	TOK_EQUAL = '=',
	TOK_NAME = 'a'
};

typedef struct s_token
{
	char				*token;
	enum e_token_types	type;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

//--array=======================================================================
int					is_delimiter(char c);
void				jump_delimiters(char *input, int *i, int curr_char_type);
void				insert_non_text_tokens(char *input, char **tokens_node, \
													int *j, int curr_char_type);

//--list========================================================================
t_token				*tlst_new_node(char *token);
void				token_lstadd_back(t_token **t_lst_head, t_token *new_node);
enum e_token_types	get_token_type(char *token);

#endif