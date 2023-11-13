/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_echo_exit_pwd.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:42:11 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/28 13:42:11 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

void	builtin_echo(t_data *dat, t_exec *exec)
{
	char	**argv;
	int		i;
	int		start;

	(void) dat;
	argv = exec->my_node->argv;
	if (!argv[1])
	{
		printf("\n");
		return ;
	}
	start = 1;
	if (ft_strncmp("-n", argv[1], 2) == 0)
		start = 2;
	i = start;
	while (argv[i])
	{
		if (i != start)
			printf(" ");
		printf("%s", argv[i]);
		i++;
	}
	if (start == 1)
		printf("\n");
}

void	builtin_pwd(t_data *dat, t_exec *exec)
{
	char	buffer[PATH_MAX];

	(void) dat;
	(void) exec;
	ft_bzero(buffer, PATH_MAX);
	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		ft_printf_err("Hellshell: %s\n", strerror(errno));
		assign_exit_val(dat->varlist, errno);
	}
	else
		printf("%s\n", buffer);
}

void	builtin_exit(t_data *dat, t_exec *exec)
{
	int	i;

	(void) exec;
	(void) dat;
	if (!exec->my_node->argv[1])
		exit(EXIT_SUCCESS);
	i = 0;
	while (exec->my_node->argv[1][i])
	{
		if (!ft_isdigit(exec->my_node->argv[1][i]) || i > 2)
		{
			ft_printf_err("%s: %s: numeric argument between 0 and 255 required"\
			, exec->my_node->argv[0], exec->my_node->argv[1]);
			exit(2);
		}
		i++;
	}
	i = ft_atoi(exec->my_node->argv[1]);
	if (i > 255)
	{
		ft_printf_err("%s: %s: numeric argument between 0 and 255 required"\
		, exec->my_node->argv[0], exec->my_node->argv[1]);
		exit(2);
	}
	exit(i);
}

// Move to different folder.
void	builtin_cd(t_data *dat, t_exec *exec)
{
	t_envlst	*oldpwd;
	char		buffer[PATH_MAX];

	(void) dat;
	if (!exec->my_node->argv[1])
		return ;
	ft_bzero(buffer, PATH_MAX);
	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		ft_printf_err("Hellshell: %s\n", strerror(errno));
		assign_exit_val(dat->varlist, errno);
	}
	if (chdir(exec->my_node->argv[1]) == -1)
	{
		ft_printf_err("Hellshell: %s: %s\n", \
		exec->my_node->argv[1], strerror(errno));
		assign_exit_val(dat->varlist, errno);
	}
	oldpwd = check_var_existence(dat->envlist, "OLDPWD");
	if (oldpwd)
		change_existing_val_alt(oldpwd, buffer);
	else
	{
		oldpwd = newnode_env_alt("OLDPWD", buffer);
		envlst_addback(dat->envlist, oldpwd);
	}
	dat->envp = set_envp(dat->envlist, dat->envp);
}
