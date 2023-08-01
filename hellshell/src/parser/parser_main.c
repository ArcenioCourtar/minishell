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

/** QUOTES
 * state SPACE or NOSPACE before quote
 * if SPACE
 * 		in state S/D QUOTE 
 * 				something
 * if NOSPACE
 * 		in state S/D QUOTE
 * 				append to what's before
 * 				delete quotes token from list
 */

void	create_cmd_lst(t_data *data, t_cmd **cmd_lst_head);

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
	return (p_data);
}

void	parser(t_data *data)
{
	t_cmd			**cmd_lst_head;

	cmd_lst_head = (t_cmd **)malloc(sizeof(t_cmd *));
	if (!cmd_lst_head)
		ft_error(errno, strerror(errno));
	*cmd_lst_head = NULL;
	create_cmd_lst(data, cmd_lst_head);
}
