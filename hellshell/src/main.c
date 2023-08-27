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

int	main(int argc, char **argv, char **envp)
{
	t_data	dat;

	(void) argv;
	(void) argc;

	init_dat(&dat, envp);
	while (1)
	{
		dat.input = readline("\x1b[31mhellshell-0.2$\x1b[37m ");
		if (!dat.input)
			break ;
		add_history(dat.input);
		quotes_check(dat);
		lexer(&dat);
		parser(&dat);
		finalize_cmd_list(dat.cmd_lst);
		executor(&dat);
		cmdlst_free(&dat);
		free(dat.input);
		free(dat.t_lst);
		free(dat.tokens);
	}
	exit(EXIT_SUCCESS);
}
