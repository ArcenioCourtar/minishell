/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_list_final.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/10 15:35:53 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/10 15:35:53 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

bool	check_path(char *path)
{
	if (ft_strchr(path, '/') != NULL)
		return (true);
	return (false);
}

void	finalize_cmd_list(t_cmdlst **list)
{
	t_cmdlst	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp->fd_in = STDIN_FILENO;
		tmp->fd_out = STDOUT_FILENO;
		tmp->abs_path = check_path(tmp->argv[0]);
		tmp = tmp->next;
	}
}
