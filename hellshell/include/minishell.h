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
# define BT_NUM 9
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include "lexer.h"
# include "executor.h"

typedef struct s_exec	t_exec;
typedef struct s_cmdlst	t_cmdlst;
typedef void			(*t_builtin_func)(t_data *, t_exec *);

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
t_envlst	*newnode_env(char *envp);
void		envlst_addback(t_envlst *list, t_envlst *new);
void		envlst_move_node(t_envlst *node, t_envlst *dst);
void		envlst_free_node(t_envlst *del);
void		varlst_add_back(t_data *data, t_envlst *new_node);
char		**set_envp(t_envlst *envlist, char **envp);
void		init_dat(t_data *dat, char **envp);

void		lexer(t_data *data);

int			parser(t_data *data);
void		cmdlst_free(t_data *data);

void		signals_interactive_mode(void);
void		signals_in_process(void);


/* init---------------------------------------------------------------------- */
t_cmdlst	**init_command_list(void);

/* free---------------------------------------------------------------------- */
void		to_freelstfree(t_freelst **lst);
int			ft_fd_printf(int fd, const char *s, ...);

/* testing------------------------------------------------------------------- */
void		print_token_array(t_data dat);
void		print_token_list(t_data dat);
void		print_envlst(t_envlst *start);

#endif