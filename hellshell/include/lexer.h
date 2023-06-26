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

// types
# define IDEN 0
# define CONS 1
# define OPRS 0
# define SEPS 0
# define KEYW 0
# define IDEN 0


#endif