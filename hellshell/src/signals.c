/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/29 19:48:46 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/29 19:48:46 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include "minishell.h"

// handles CTRL+C (SIGINT) in interactive mode
// displays a new prompt on a newline and clears current rl buffer
static void	sigint_handler(int signum)
{
	g_signal = signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// handles SIGINT & SIGQUIT in interactive mode
// CTRL+C (SIGINT) is handled
// CTRL+\ (SIGQUIT) is ignored
void	signals_interactive_mode(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_other(int signum)
{
	g_signal = signum;
}
