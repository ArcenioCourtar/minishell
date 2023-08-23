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

void	envlist_addback(t_envlst **list, t_envlst *new)
{
	t_envlst	*last;

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

static t_envlst	*check_var_existence(t_data *dat, char *var)
{
	t_envlst	*tmp;
	int			namelen;

	tmp = dat->envlist;
	if (ft_strchr(var, '=') == NULL)
		namelen = ft_strlen(var);
	else
		namelen = ft_strchr(var, '=') - var;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->name, namelen) == 0)
			return (NULL);
		tmp = tmp->next;
	}
	return (tmp);
}

void	*change_existing_val(t_envlst *node, char *var)
{
	(void) node;
	var = ft_strchr(var, '=');
	printf("test: %s\n", var);
	return (NULL);
}

void	builtin_export(t_data *dat, t_exec *exec)
{
	t_envlst	*new;

	(void) new;
	(void) dat;
	if (exec->my_node->argv[1] == NULL)
		return ;
	new = check_var_existence(dat, exec->my_node->argv[1]);
	if (new == NULL)
	{
		newnode_env(exec->my_node->argv[1]);
	}
	else
	{
		change_existing_val(new, exec->my_node->argv[1]);
	}
}

void	remove_envnode(t_envlst *start, t_envlst *node)
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
void	builtin_unset(t_data *dat, t_exec *exec)
{
	t_envlst	*p;

	(void) exec;
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
