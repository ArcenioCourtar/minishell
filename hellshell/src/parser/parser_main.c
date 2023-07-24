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

/** PARSING ORDER
 * quotes
 * heredoc
 * pipes i guess
 * expanding
 * put everything together
 */

void	create_command_table(t_data *data, t_parser_data *p_data);

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
	*new_table = NULL;
	return (new_table);
}

t_parser_data	*init_parser_data(void)
{
	t_parser_data	*p_data;

	p_data = (t_parser_data *)ft_calloc(1, sizeof(t_parser_data));
	if (!p_data)
		ft_error(errno, strerror(errno));
	p_data->cmd_table = (t_cmd **)ft_calloc(1, sizeof(t_cmd *));
	if (!p_data->cmd_table)
		ft_error(errno, strerror(errno));
	p_data->io_redirects = (t_inout *)malloc(sizeof(t_inout));
	if (!p_data->io_redirects)
		ft_error(errno, strerror(errno));
	return (p_data);
}

void	parser(t_data *data)
{
	t_inout			io_redirect;
	t_parser_data	*p_data;

	p_data = init_parser_data();
	/*handle quotes and heredoc */
	init_io_redirect(&io_redirect);
	// if (state == CMD)
	create_command_table(data, p_data);
	// redirects(*data);
}
