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
# include "lexer.h"

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
	int					tok_count;
	struct s_token		**t_lst;
	struct s_hislst		**h_lst;
}	t_data;

typedef struct s_envlist
{
	int					size;
	char				*name;
	char				*value;
	struct s_envlist	*next;
	struct s_envlist	*prev;
}	t_envlist;

// history
t_hislst	**history_list_init(void);
void		add_to_history_list(t_hislst **history_list, char *input);
void		print_history_list(t_hislst **history_list);

t_envlist	*init_envlist(char **envp);
char		**set_envp(t_envlist *envlist, char **envp);
void		init_dat(t_data *dat, char **envp);
void		execute_command(t_data *dat);

void		lexer(t_data *data);

//--testing---------------------------------------------------------------------
void		print_token_array(t_data dat);
void		print_token_list(t_data dat);

#endif