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

void	parser(t_data *data)
{
	quotes(data, data->t_lst);
	create_cmd_lst(data);
}
