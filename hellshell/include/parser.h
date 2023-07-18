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

typedef struct s_cmd
{
	char			*command;
	char			**argv;
	char			**envp;
	struct s_cmdlst	*next;
}	t_cmd;

typedef struct s_inout
{
	char	*infile;
	char	*outfile;
	char	*error;
}	t_inout;

typedef struct s_parser_data
{
	struct s_cmd	**cmd_table;
	struct s_inout	io_redirects;
	char			**redirect_files;
}	t_parser_data;

void	redirects(t_data data);

#endif