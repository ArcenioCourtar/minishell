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
# define BT_NUM 7
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include "lexer.h"
# include "executor.h"

typedef void			(*t_builtin_func)(t_data *);
typedef struct s_cmdlst	t_cmdlst;

typedef struct s_hislst
{
	int				n;
	char			*command;
	struct s_hislst	*next;
}	t_hislst;

typedef struct s_freelst
{
	char				*string;
	struct s_freelst	*next;
}	t_freelst;

typedef struct s_data
{
	char				*input;
	char				**envp;
	struct s_envlst		*envlist;
	struct s_envlst		*varlist;
	char				**tokens;
	int					tok_count;
	struct s_toklst		**t_lst;
	struct s_hislst		**h_lst;
	struct s_cmdlst		**cmd_lst;
	char				builtin_index[BT_NUM][10];
	t_builtin_func		builtin_ptrs[BT_NUM];
	t_builtin_func		test;
	struct s_freelst	**free_lst;
}	t_data;

typedef struct s_envlst
{
	int					size;
	char				*name;
	char				*value;
	struct s_envlst		*next;
	struct s_envlst		*prev;
}	t_envlst;

/* history------------------------------------------------------------------- */
t_hislst	**init_history_list(void);
void		add_to_history_list(t_hislst **history_list, char *input);
void		print_history_list(t_hislst **history_list);

t_envlst	*init_envlst(char **envp);
char		**set_envp(t_envlst *envlist, char **envp);
void		init_dat(t_data *dat, char **envp);
void		execute_command(t_data *dat);

void		lexer(t_data *data);

int			parser(t_data *data);
void		cmdlst_free(t_data *data);

/* init---------------------------------------------------------------------- */
t_cmdlst	**init_command_list(void);

/* error checking------------------------------------------------------------ */
int			quotes_check(t_data data);

/* free---------------------------------------------------------------------- */
void		to_freelstfree(t_freelst **lst);

/* testing------------------------------------------------------------------- */
void		print_token_array(t_data dat);
void		print_token_list(t_data dat);

#endif