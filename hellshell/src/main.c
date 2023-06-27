/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/20 13:21:43 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/20 17:41:36 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void	init_dat(t_data *dat, char **envp)
{
	dat->input = NULL;
	dat->envp = envp;
	dat->envlist = init_envlist(envp);
}

void	execute_command(t_data *dat)
{
	if (!ft_strncmp(dat->input, "env", 3))
		builtin_env(dat->envp);
}
/*
	builtin time!
	echo (with -n)
	cd with relative/abs path
	pwd
	export
	unset
	env
	exit
*/
int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		**tokens;
	t_hislst	**h_lst;
	int			i;
	t_data	dat;

	(void) argv;
	(void) argc;

	init_dat(&dat, envp);
	while (1)
	{
		input = readline("hellshell-0.1$ ");
		if (!input)
			break ;
		add_history(input);
		add_to_history_list(h_lst, input);
		tokens = lexer(input);
		i = 0;
		while (tokens[i])
		{
			ft_printf("%s\n", tokens[i]);
			i++;
		}
		dat.input = readline("hellshell v0.1$ ");
		execute_command(&dat);
		free(dat.input);
	}
	exit(EXIT_SUCCESS);
}
