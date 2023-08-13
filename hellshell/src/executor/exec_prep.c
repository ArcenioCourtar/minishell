/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_prep.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/13 18:19:57 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/13 18:19:57 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include "parser.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>

bool	find_pathvar(char **envp, t_exec *exec)
{
	int		i;

	i = 0;
	exec->path_avail = false;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (true);
	exec->path_avail = true;
	exec->path_list = ft_split(envp[i] + 5, ':');
	if (exec->path_list == NULL)
		return (false);
	return (true);
}

int	count_forks(t_cmdlst **list)
{
	t_cmdlst	*tmp;
	int			count;

	tmp = *list;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
