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

// static void	leaks(void)
// {
// 	system("leaks -q hellshell");
// }

void	init_dat(t_data *dat)
{
	dat->input = NULL;
	dat->start = NULL;
	dat->hist = NULL;
}

t_tokens	tokenizer(char *input)
{
	t_tokens	*new;
	int			i;

	new = NULL;
	i = 0;
}

int	main(void)
{
	t_data	dat;

	init_dat(&dat);
	while (1)
	{
		dat.input = readline("hellshell v0.1$ ");
		
		free(dat.input);
	}
	exit(EXIT_SUCCESS);
}

// t_hislst	**h_lst;

	// atexit(leaks);
	// h_lst = history_list_init();
	// while (1)
	// {
	// 	input = readline("hellshell-0.1$ ");
	// 	if (!input)
	// 		break ;
	// 	add_history(input);
	// 	add_to_history_list(h_lst, input);
	// 	ft_printf("%s\n", input);
	// }
	// ft_printf("\n");
	// print_history_list(h_lst);