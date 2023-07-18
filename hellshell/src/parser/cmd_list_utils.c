/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 14:09:12 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/07/18 14:09:12 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "libft.h"

t_cmd	*cmdlst_new_node(char *command, char **argv)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		ft_error(errno, strerror(errno));
	new_node->command = command;
	new_node->argv = argv;
	new_node->envp = NULL;
	new_node->next = NULL;
}
