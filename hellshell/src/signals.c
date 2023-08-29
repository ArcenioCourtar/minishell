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
#include <stdio.h>


// CTRL+C in process
// acts like bash

// CTRL+D in process
// acts like bash

// CTRL+D in interactive mode
// exits the shell

// CTRL+C (SIGINT) in interactive mode
// displays a new prompt on a newline and clears current rl buffer
void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// CTRL+\ (SIGQUIT) is always ignored
void	signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
