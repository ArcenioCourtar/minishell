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

# include <sys/types.h>
# include <stdbool.h>

typedef struct s_data	t_data;
typedef struct s_toklst	t_toklst;
enum					e_token_type;

enum e_st_space
{
	SPACE,
	NOSPACE,
	FIRST
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
	int					pipe[2];
	int					heredoc[2];
	int					fd_in;
	int					fd_out;
	bool				abs_path;
	pid_t				pid;
}	t_cmdlst;

int			create_cmd_lst(t_data *data);

//--new node====================================================================
int			redirects_to_node(t_toklst *token, t_cmdlst *node);
void		argv_to_node(t_toklst *token, t_cmdlst *node);
////--utils=====================================================================
int			argv_count(t_toklst *t_lst);
int			count_redirs(t_toklst *token);
bool		is_redirect(enum e_token_type type);
void		print_redirect_error(t_toklst *token);
void		skip_redirects(t_toklst **token);

//--quotes======================================================================
void		handle_quotes(t_data *data, t_toklst **token);
void		quote_join(t_data *data, t_toklst **token, bool joinaddback);

//--expansion===================================================================
void		expansion(t_data *data, t_toklst **token);
bool		check_for_dollar(char *token);
char		*getvar(t_data *data, char *to_expand, bool in_quotes);
////--quotes====================================================================
void		expand_in_quotes(t_data *data, t_toklst *token);
int			count_dollar_signs(char *token);
int			exp_strlen(char *token, char **expansions);
void		cpy_expansion(char **exp_str, int *i, char *expansion);
bool		is_valid_var(char c);

//--command list functions======================================================
t_cmdlst	*cmdlst_new_node(void);
void		cmdlst_add_back(t_cmdlst **cmd_lst_head, t_cmdlst *new_node);

//--rest========================================================================
void		add_to_free_lst(t_data *data, char *content);
void		token_lstfree(t_toklst **t_lst);
void		token_lstdel_node(t_toklst **token);
int			syntax_error_checks(t_data *data);

//--testing=====================================================================
void		printf_cmd_table(t_cmdlst **cmd_table_head);

#endif