/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_main.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 13:05:17 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/30 13:05:17 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

void	init_io_redirect(t_inout *io_redirect)
{
	io_redirect->infile = NULL;
	io_redirect->outfile = NULL;
	io_redirect->error = NULL;
}

t_cmd	**init_cmd_table(void)
{
	t_cmd	**new_table;

	new_table = (t_cmd **)malloc(sizeof(t_cmd *));
	if (!new_table)
		ft_error(errno, strerror(errno));
	*new_table = 0;
	return (new_table);
}

t_parser_data	*init_parser_data(t_cmd **cmd_table)
{
	t_parser_data	*p_data;

	p_data = (t_parser_data *)malloc(sizeof(t_parser_data));
	if (!p_data)
		ft_error(errno, strerror(errno));
	p_data->cmd_table = cmd_table;
	return (p_data);
}

void	parser(t_data *data)
{
	// t_cmd			**cmd_table;
	t_inout			io_redirect;
	// t_parser_data	*p_data;

	// p_data = init_parser_data();
	init_io_redirect(&io_redirect);
	redirects(*data);
}
