/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 18:58:14 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/28 18:58:14 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

int	strchrloc(char *s, int c)
{
	int	i;
	int	len_s;

	i = 0;
	len_s = ft_strlen(s);
	while (i <= len_s)
	{
		if (s[i] == (char)c)
			return (i);
		else
			i++;
	}
	return (-1);
}

void	envlist_addback(t_envlist *list, t_envlist *new)
{
	t_envlist	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// TODO: prevent duplicate variables
void	builtin_export(t_data *dat)
{
	t_envlist	*new;
	int			equalsloc;

	// if valid
	new = malloc(sizeof(t_envlist));
	if (!new)
		ft_error(errno, "malloc\n");
	equalsloc = strchrloc(dat->tokens[2], '=');
	if (equalsloc == 0)
		return ;
	else if (equalsloc == -1)
	{
		new->name = ft_substr(dat->tokens[2], 0, ft_strlen(dat->tokens[2]));
		if (!new->name)
			ft_error(errno, "malloc\n");
		new->value = malloc(1);
		if (!new->value)
			ft_error(errno, "malloc\n");
		new->value[0] = '\0';
	}
	else
	{
		new->name = ft_substr(dat->tokens[2], 0, equalsloc);
		if (!new->name)
			ft_error(errno, "malloc\n");
		new->value = ft_substr(dat->tokens[2], equalsloc + 1, ft_strlen(dat->tokens[2]) - equalsloc);
		if (!new->value)
			ft_error(errno, "malloc\n");
	}
	envlist_addback(dat->envlist, new);
	dat->envp = set_envp(dat->envlist);
}