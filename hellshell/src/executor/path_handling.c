/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 15:36:41 by acourtar      #+#    #+#                 */
/*   Updated: 2023/11/16 15:36:41 by acourtar      ########   odam.nl         */
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

static void	absolute_path_wrapper(t_exec *exec, char *command)
{
	ft_strlcpy(exec->cmd, command, ft_strlen(command) + 1);
	if (access(command, X_OK) == -1)
	{
		ft_printf_err("hellshell: %s: %s\n", command, strerror(errno));
		if (errno == 13)
			exit(126);
		exit(127);
	}
}

static bool	relative_path_wrapper(t_exec *exec, char *command)
{
	int		i;

	i = 0;
	while (exec->path_list[i])
	{
		ft_strlcpy(exec->cmd, exec->path_list[i], \
		ft_strlen(exec->path_list[i]) + 1);
		ft_strlcpy(exec->cmd + ft_strlen(exec->path_list[i]), "/", 2);
		ft_strlcpy(exec->cmd + ft_strlen(exec->path_list[i]) + 1, \
		command, ft_strlen(command) + 1);
		if (access(exec->cmd, F_OK) == 0)
		{
			if (access(exec->cmd, X_OK) == 0)
				return (true);
			ft_printf_err("hellshell: %s: %s\n", command, strerror(errno));
			if (errno == 13)
				exit(126);
			exit(127);
		}
		i++;
	}
	return (false);
}

// TODO: return specific codes for permission issues and file not found.
void	find_path(t_exec *exec)
{
	char	*command;

	command = exec->my_node->argv[0];
	if (ft_strlen(command) == 0)
	{
		ft_printf_err("hellshell: %s: command not found\n", command);
		exit(127);
	}
	exec->cmd = malloc(exec->path_maxlen + ft_strlen(command) + 2);
	if (!exec->cmd)
	{
		ft_printf_err("hellshell: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (exec->path_avail == 0 || exec->my_node->abs_path == true)
	{
		absolute_path_wrapper(exec, command);
		return ;
	}
	if (relative_path_wrapper(exec, command))
		return ;
	ft_printf_err("hellshell: %s: command not found\n", command);
	exit(127);
}

static void	find_max_pathlen(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->path_list[i])
	{
		if (ft_strlen(exec->path_list[i]) > exec->path_maxlen)
			exec->path_maxlen = ft_strlen(exec->path_list[i]);
		i++;
	}
}

bool	find_pathvar(char **envp, t_exec *exec)
{
	int		i;

	i = 0;
	exec->path_maxlen = 0;
	exec->path_avail = false;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
	{
		exec->path_list = NULL;
		return (true);
	}
	exec->path_avail = true;
	exec->path_list = ft_split(envp[i] + 5, ':');
	if (exec->path_list == NULL)
		return (false);
	find_max_pathlen(exec);
	return (true);
}
