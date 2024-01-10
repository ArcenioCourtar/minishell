/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_pwd.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/23 18:44:23 by acourtar      #+#    #+#                 */
/*   Updated: 2023/11/23 18:44:23 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	oldpwd_assignment(t_data *dat, char *buffer)
{
	t_envlst	*oldpwd;

	oldpwd = check_var_existence(dat->envlist, "OLDPWD");
	if (oldpwd)
	{
		if (!change_existing_val_alt(oldpwd, buffer))
		{
			ft_printf_err("Hellshell: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		oldpwd = newnode_env_alt("OLDPWD", buffer);
		if (!oldpwd)
		{
			ft_printf_err("Hellshell: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		envlst_addback(&(dat->envlist), oldpwd);
	}
}

void	builtin_pwd(t_data *dat, t_exec *exec)
{
	char	buffer[PATH_MAX + 1];

	(void) exec;
	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		ft_printf_err("Hellshell: %s\n", strerror(errno));
		assign_exit_val(dat->exit_code, 1);
	}
	else
	{
		printf("%s\n", buffer);
		assign_exit_val(dat->exit_code, 0);
	}
}

static bool	cd_error(t_data *dat, t_exec *exec, char *buffer)
{
	if (exec->my_node->argv[2])
	{
		ft_printf_err("hellshell: cd: too many arguments\n");
		assign_exit_val(dat->exit_code, 1);
		return (true);
	}
	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		ft_printf_err("Hellshell: %s\n", strerror(errno));
		assign_exit_val(dat->exit_code, 1);
		return (true);
	}
	if (chdir(exec->my_node->argv[1]) == -1)
	{
		ft_printf_err("Hellshell: %s: %s\n", \
		exec->my_node->argv[1], strerror(errno));
		assign_exit_val(dat->exit_code, 1);
		return (true);
	}
	return (false);
}

void	builtin_cd(t_data *dat, t_exec *exec)
{
	char		buffer[PATH_MAX + 1];

	if (!exec->my_node->argv[1])
	{
		return ;
		assign_exit_val(dat->exit_code, 0);
	}
	if (cd_error(dat, exec, buffer))
		return ;
	oldpwd_assignment(dat, buffer);
	dat->envp = set_envp(dat->envlist, dat->envp);
	assign_exit_val(dat->exit_code, 0);
}
