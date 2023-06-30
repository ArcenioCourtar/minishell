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

void	envlist_addback(t_envlist **list, t_envlist *new)
{
	t_envlist	*last;

	if (*list == NULL)
		*list = new;
	else
	{
		last = *list;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

// TODO: prevent duplicate variables
// use the function you created to initialize this type xd dumbo
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
	new->next = NULL;
	new->prev = NULL;
	new->size = ft_strlen(new->name) + ft_strlen(new->value) + 2;
	envlist_addback(&dat->envlist, new);
	dat->envp = set_envp(dat->envlist, dat->envp);
}

void	remove_envnode(t_envlist *start, t_envlist *node)
{
	if (start == node)
	{
		start = node->next;
		start->prev = NULL;
	}
	else
	{
		node->prev->next = node->next;
		if (node->next != NULL)
			node->next->prev = node->prev;
	}

	free(node->name);
	free(node->value);
	free(node);
}

// TODO add non-env variable declaration, and unsetting
void	builtin_unset(t_data *dat)
{
	t_envlist	*p;

	p = dat->envlist;
	while (p)
	{
		if (compare_token(dat->tokens, 2, p->name))
		{
			remove_envnode(dat->envlist, p);
			dat->envp = set_envp(dat->envlist, dat->envp);
			break ;
		}
		p = p->next;
	}
}
