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
	dat->h_lst = history_list_init();
}

void	execute_command(t_data *dat)
{
	if (!ft_strncmp(dat->input, "env", 3))
		builtin_env(dat->envp);
	if (!ft_strncmp(dat->input, "history", 8))
		print_history_list(dat->h_lst);
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
	// int		i;
	t_data	dat;

	(void) argv;
	(void) argc;

	init_dat(&dat, envp);
	while (1)
	{
		dat.input = readline("hellshell-0.1$ ");
		if (!dat.input)
			break ;
		add_history(dat.input);
		add_to_history_list(&dat);
		dat.tokens = lexer(dat.input);
		// i = 0;
		// while (dat.tokens[i])
		// {
		// 	ft_printf("%i: %s\n", i, dat.tokens[i]);
		// 	i++;
		// }
		execute_command(&dat);
		free(dat.input);
	}
	exit(EXIT_SUCCESS);
}
