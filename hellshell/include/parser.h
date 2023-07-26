/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 13:04:37 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/30 13:04:37 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum e_cmd_type
{
	CMD_FIRST,
	CMD_PIPE,
	CMD_REDIN = '<',
	CMD_REDOUT = '>',
	CMD_REDAPPEND = '>' / 2,
	CMD_HEREDOC = '<' / 2
};

enum e_redir_type
{
	REDIN = '<',
	REDOUT = '>',
	REDAPPEND = '>' / 2,
	HEREDOC = '<' / 2
};

typedef struct s_redirect
{
	char				*name;
	enum e_redir_type	type;
}	t_redirect;

typedef struct s_cmd
{
	char				**argv;
	struct s_redirect	*redirect;
	// char				**envp;
	enum e_cmd_type		type;
	struct s_cmd		*prev;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_parser_data
{
	struct s_cmd	**cmd_table;
	// struct s_inout	*io_redirects;
	char			**redirect_files;
}	t_parser_data;

enum	e_p_states
{
	ST_DQUOTE,
	ST_SQUOTE
};

void	cmdlst_add_back(t_cmd **cmd_lst_head, t_cmd *new_node);
t_cmd	*cmdlst_new_node(void);
int		count_redirs(t_token *token);
int		argv_count(t_token *t_lst);
void	skip_redirects(t_token **token);
bool	is_redirect(enum e_token_types type);

// testing
void	printf_cmd_table(t_cmd **cmd_table_head);

#endif