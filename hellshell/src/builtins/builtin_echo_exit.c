/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo_exit.c                                :+:    :+:            */
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
	int		i;
	int		start;

	if (!exec->my_node->argv[1])
	{
		printf("\n");
		assign_exit_val(dat->exit_code, 0);
		return ;
	}
	start = 1;
	if (ft_strncmp("-n", exec->my_node->argv[1], 2) == 0)
		start = 2;
	i = start;
	while (exec->my_node->argv[i])
	{
		if (i != start)
			printf(" ");
		printf("%s", exec->my_node->argv[i]);
		i++;
	}
	if (start == 1)
		printf("\n");
	assign_exit_val(dat->exit_code, 0);
}

static bool	exit_arg_isnum(t_exec *exec)
{
	int		i;
	char	*arg;

	arg = exec->my_node->argv[1];
	if (arg[0] != '+' && arg[0] != '-' && !ft_isdigit(arg[0]))
		return (false);
	i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

void	builtin_exit(t_data *dat, t_exec *exec)
{
	int	exit_val;

	if (!exec->my_node->argv[1])
		exit(EXIT_SUCCESS);
	if (exec->my_node->argv[2])
	{
		ft_printf_err("exit: too many arguments\n");
		assign_exit_val(dat->exit_code, 1);
		return ;
	}
	if (!exit_arg_isnum(exec))
	{
		ft_printf_err("exit: %s: numeric argument required\n", \
		exec->my_node->argv[1]);
		exit(2);
	}
	exit_val = ft_atoi(exec->my_node->argv[1]);
	exit(exit_val);
}
