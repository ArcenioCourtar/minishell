/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals_new.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/19 20:30:41 by acourtar      #+#    #+#                 */
/*   Updated: 2023/12/19 20:30:41 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include "minishell.h"

void	signals_interactive(int signum)
{
	(void) signum;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals_heredoc_new(int signum)
{
	g_signal = signum;
}

void	signals_other(int signum)
{
	g_signal = signum;
}
