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

int	main(void)
{
	char		*input;
	t_hislst	**h_lst;

	// atexit(leaks);
	h_lst = history_list_init();
	while (1)
	{
		input = readline("hellshell-0.1$ ");
		if (!input)
			break ;
		add_history(input);
		add_to_history_list(h_lst, input);
		ft_printf("%s\n", input);
	}
	ft_printf("\n");
	print_history_list(h_lst);
	exit(EXIT_SUCCESS);
}
