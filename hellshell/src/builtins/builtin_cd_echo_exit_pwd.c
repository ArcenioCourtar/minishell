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
		if (i != 1)
			printf(" ");
		printf("%s", argv[i]);
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
		ft_printf_err("Hellshell: %s\n", strerror(errno));
		// set ? var
	}
	else
		printf("%s\n", buffer);
}

void	builtin_exit(t_data *dat, t_exec *exec)
{
	(void) exec;
	(void) dat;
	exit(EXIT_SUCCESS);
}

// TODO: add OLDPWD to env upon use
void	builtin_cd(t_data *dat, t_exec *exec)
{
	(void) dat;
	if (!exec->my_node->argv[1])
		return ;
	if (chdir(exec->my_node->argv[1]) == -1)
	{
		ft_printf_err("Hellshell: %s: %s\n", \
		exec->my_node->argv[1], strerror(errno));
		// assign errno to ?
	}
}
