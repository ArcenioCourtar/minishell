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
#include "builtins.h"
#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_signal = 0;

/**
 * @brief frees the current input data
 * @param data pointer to the program data struct
 */
static void	free_current_input_data(t_data *data)
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

static int	executor_wrapper(t_data	*dat)
{
	finalize_cmd_list(dat->cmd_lst);
	executor(dat);
	return (ft_atoi(dat->exit_code->value));
}

void	redisplay_prompt(void)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

/*
	readline return values
	returns NULL if EOF is encountered and input is empty
	EOF is treated as newline if string is not empty
*/
int	main(int argc, char **argv, char **envp)
{
	t_data	dat;
	int		exit_status;

	exit_status = 0;
	(void) argv;
	(void) argc;
	init_dat(&dat, envp);
	while (1)
	{
		if (g_signal)
			redisplay_prompt();
		g_signal = 0;
		signal(SIGINT, signals_interactive);
		signal(SIGQUIT, SIG_IGN);
		dat.input = readline("➤ hellshell-0.9$ ");
		signal(SIGINT, signals_other);
		if (!dat.input)
		{
			printf("exit\n");
			break ;
		}
		add_history(dat.input);
		lexer(&dat);
		exit_status = parser(&dat);
		if (!exit_status)
			exit_status = executor_wrapper(&dat);
		free_current_input_data(&dat);
	}
	exit(EXIT_SUCCESS);
}
