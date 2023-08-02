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

enum e_state_space
{
	SPACE,
	NOSPACE,
	NOTOK
};

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

typedef struct s_cmdlst
{
	char				**argv;
	struct s_redirect	*redirect;
	enum e_cmd_type		type;
	struct s_cmdlst		*prev;
	struct s_cmdlst		*next;
}	t_cmdlst;

typedef struct s_parser_data
{
	struct s_cmdlst	**cmd_table;
	char			**redirect_files;
}	t_parser_data;

enum	e_p_states
{
	ST_DQUOTE,
	ST_SQUOTE
};

void		redirect_error(t_toklst *token);
void		skip_redirects(t_toklst **token);
int			count_redirs(t_toklst *token);
int			argv_count(t_toklst *t_lst);
bool		is_redirect(enum e_token_types type);

// command list functions
t_cmdlst	**init_command_list(void);
t_cmdlst	*cmdlst_new_node(void);
void		cmdlst_add_back(t_cmdlst **cmd_lst_head, t_cmdlst *new_node);
void		cmdlst_del_node(t_toklst **token);


// testing
void		printf_cmd_table(t_cmdlst **cmd_table_head);

#endif