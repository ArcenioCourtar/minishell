/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins3.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 19:00:22 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/28 19:00:22 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

void	builtin_env(t_data *dat, t_exec *exec)
{
	int	i;

	(void) exec;
	i = 0;
	while (dat->envp[i])
	{
		printf("%s\n", dat->envp[i]);
		i++;
	}
}

// still needs -n
void	builtin_echo(t_data *dat, t_exec *exec)
{
	char	**argv;
	int		i;

	(void) dat;
	argv = exec->my_node->argv;
	i = 1;
	while (argv[i])
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
}

void	builtin_pwd(t_data *dat, t_exec *exec)
{
	char	buffer[MAX_PATH];

	(void) dat;
	(void) exec;
	ft_bzero(buffer, MAX_PATH);
	if (getcwd(buffer, MAX_PATH) == NULL)
	{
		ft_fd_printf(STDERR_FILENO, "Hellshell: %s\n", strerror(errno));
		// set ? var
	}
	else
		printf("%s\n", buffer);
}

// add OLDPWD to env upon use
void	builtin_cd(t_data *dat, t_exec *exec)
{
	(void) dat;
	if (!exec->my_node->argv[1])
		return ;
	if (chdir(exec->my_node->argv[1]))
	{
		ft_fd_printf(STDERR_FILENO, "Hellshell: %s: %s\n", \
		exec->my_node->argv[1], strerror(errno));
		// assign errno to ?
	}
}

void	builtin_exit(t_data *dat, t_exec *exec)
{
	(void) exec;
	(void) dat;
	exit(EXIT_SUCCESS);
}

void	builtin_var_assign(t_data *dat, t_exec *exec)
{
	t_envlst	*new;

	new = check_var_existence(dat->varlist, exec->my_node->argv[0]);
	if (new == NULL)
	{
		new = check_var_existence(dat->envlist, exec->my_node->argv[0]);
		if (new == NULL)
		{
			new = newnode_env(exec->my_node->argv[0]);
			envlst_addback(dat->varlist, new);
		}
		else
		{
			change_existing_val(new, exec->my_node->argv[0]);
			dat->envp = set_envp(dat->envlist, dat->envp);
		}
	}
	else
	{
		change_existing_val(new, exec->my_node->argv[0]);
	}
}
void	builtin_var(t_data *dat, t_exec *exec)
{
	(void) exec;
	print_envlst(dat->varlist);
}
