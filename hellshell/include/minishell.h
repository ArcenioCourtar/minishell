/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 13:21:58 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/20 17:01:53 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

enum e_token {
	TOK_DQUOTE = '"',
	TOK_SQUOTE = '\'',
	TOK_NAME = 'a',
	TOK_PIPE = '|',
	TOK_REDIN = '<',
	TOK_REDOUT = '>',
	TOK_REDAPPEND = '>' * 2,
	TOK_HEREDOC = '<' * 2,
	TOK_DOLLAR = '$',
	TOK_ESCAPE = '\\'
};

typedef struct s_data
{
	char			*input;
	struct s_tokens	*start;
	struct s_hislst	*hist;
}	t_data;

typedef struct s_hislst
{
	int				n;
	char			*command;
	struct s_hislst	*next;
}	t_hislst;

typedef struct s_tokens
{
	char			*str;
	enum e_token	type;
	bool			indquotes;
	bool			insquotes;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;

// history
t_hislst	**history_list_init(void);
void		add_to_history_list(t_hislst **history_list, char *input);
void		print_history_list(t_hislst **history_list);

#endif