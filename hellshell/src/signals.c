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

// handles CTRL+C in process
// breaks out of any existing loop
static void	sigint_handler_in_process(int signum)
{
	(void)signum;
	printf("\n");
}

// handles CTRL+\ (SIGQUIT) in process
// breaks out of any existing loop and prints signal code
static void	sigquit_handler_in_process(int signum)
{
	printf("Quit: %i\n", signum);
}

// handles CTRL+C (SIGINT) in interactive mode
// displays a new prompt on a newline and clears current rl buffer
static void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

//handles SIGINT & SIGQUIT in process
void	signals_in_process(void)
{
	signal(SIGINT, sigint_handler_in_process);
	signal(SIGQUIT, sigquit_handler_in_process);
}

// handles SIGINT & SIGQUIT in interactive mode
// CTRL+C (SIGINT) is handled
// CTRL+\ (SIGQUIT) is ignored
void	signals_interactive_mode(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
