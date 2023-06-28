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

enum e_delimiters {
	DEL_DQUOTE = '"',
	DEL_SQUOTE = '\'',
	DEL_PIPE = '|',
	DEL_DOLLAR = '$',
	DEL_REDIN = '<',
	DEL_REDOUT = '>',
	DEL_SPACE = ' '
};

int		is_delimiter(char c);
void	jump_delimiters(char *input, int *i, int curr_char_type);
void	insert_non_text_tokens(char *input, char **tokens_node, \
								int *j, int curr_char_type);
char	**lexer(char *input);

#endif