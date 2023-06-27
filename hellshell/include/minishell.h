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

/*
	Required by the subject:
	' " $ < << > >> |
	NOT REQUIRED:
	\ ; && || * () 
*/
// enum e_token {
// 	TOK_DQUOTE = '"',
// 	TOK_SQUOTE = '\'',
// 	TOK_NAME = 'a',
// 	TOK_PIPE = '|',
// 	TOK_REDIN = '<',
// 	TOK_REDOUT = '>',
// 	TOK_REDAPPEND = '>' * 2,
// 	TOK_HEREDOC = '<' * 2,
// 	TOK_DOLLAR = '$',
// 	//TOK_ESCAPE = '\\'
// };

typedef struct s_hislst
{
	int				n;
	char			*command;
	struct s_hislst	*next;
}	t_hislst;

typedef struct s_data
{
	char				*input;
	char				**envp;
	struct s_envlist	*envlist;
	char				**tokens;
	struct s_hislst		**h_lst;
}	t_data;

typedef struct s_envlist
{
	int					size;
	char				*name;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

// history
t_hislst	**history_list_init(void);
void		add_to_history_list(t_data *dat);
void		print_history_list(t_hislst **history_list);

// Arcenio
t_envlist	*init_envlist(char **envp);
void		builtin_env(char **envp);

// Oliver
char	**lexer(char *input);

#endif