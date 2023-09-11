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
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include "parser.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>

// For tester compatibility
// if (!isatty(STDIN_FILENO))
// 		rl_outstream = stdin;

void	free_current_input_data(t_data *data)
{
	int	i;

	cmdlst_free(data);
	free(data->input);
	free(data->t_lst);
	to_freelstfree(data->free_lst);
	i = 0;
	while (data->tokens[i])
	{
		free(data->tokens[i]);
		data->tokens[i] = NULL;
		i++;
	}
	free(data->tokens);
}

/** readline return values
 * 	returns NULL if EOF is encountered and input is empty
 * 	EOF is treated as newline is string is not empty
 */
int	main(int argc, char **argv, char **envp)
{
	t_data	dat;

	(void) argv;
	(void) argc;
	init_dat(&dat, envp);
	while (1)
	{
		signals_interactive_mode();
		dat.input = readline("\x1b[31mhellshell-0.2$\x1b[37m ");
		if (!dat.input)
			break ;
		add_history(dat.input);
		lexer(&dat);
		if (!parser(&dat))
		{
			printf_cmd_table(dat.cmd_lst);
			finalize_cmd_list(dat.cmd_lst);
			executor(&dat);
		}
		free_current_input_data(&dat);
	}
	exit(EXIT_SUCCESS);
}
