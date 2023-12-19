/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_signals.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 15:31:06 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/12/19 15:31:06 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>

/**
 * Handles CTRL+C (SIGINT) in open heredoc
 * Breaks out of the current heredoc
 */
static void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	exit(EXIT_SUCCESS);
}

/**
 * Handles CTRL+C (SIGINT) & CTRL+\ (SIGQUIT) in heredoc
 */
void	signals_heredoc(void)
{
	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
