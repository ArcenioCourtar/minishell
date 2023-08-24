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

static t_envlst	*check_var_existence(t_envlst *list, char *var)
{
	int			namelen;

	if (ft_strchr(var, '=') == NULL)
		namelen = ft_strlen(var);
	else
		namelen = ft_strchr(var, '=') - var;
	while (list)
	{
		if (ft_strncmp(var, list->name, namelen) == 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

bool	change_existing_val(t_envlst *node, char *var)
{
	int	len;

	var = ft_strchr(var, '=') + 1;
	free(node->value);
	len = ft_strlen(var);
	node->value = malloc(len + 1);
	if (!node->value)
		return (false);
	ft_strlcpy(node->value, var, len + 1);
	node->size = ft_strlen(node->name) + len + 1;
	return (true);
}

void	envlst_addback(t_envlst *list, t_envlst *new)
{
	while (list->next)
		list = list->next;
	list->next = new;
	new->prev = list;
}

void	envlst_free_node(t_envlst *del)
{
	if (del->next)
		del->next->prev = del->prev;
	if (del->prev)
		del->prev->next = del->next;
	free(del->name);
	free(del->value);
	free(del);
}

void	builtin_export(t_data *dat, t_exec *exec)
{
	t_envlst	*new;

	(void) new;
	(void) dat;
	if (exec->my_node->argv[1] == NULL || exec->my_node->argv[1][0] == '=' || \
	ft_strchr(exec->my_node->argv[1], '=') == 0)
	{
		printf("invalid input\n");
		return ;
	}
	new = check_var_existence(dat->envlist, exec->my_node->argv[1]);
	if (new == NULL)
	{
		printf("new var\n");
		new = newnode_env(exec->my_node->argv[1]);
		envlst_addback(dat->envlist, new);
		dat->envp = set_envp(dat->envlist, dat->envp);
	}
	else
	{
		printf("existing var\n");
		change_existing_val(new, exec->my_node->argv[1]);
		dat->envp = set_envp(dat->envlist, dat->envp);
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
	t_envlst	*node;

	if (exec->my_node->argv[1] == NULL)
		return ;
	node = check_var_existence(dat->envlist, exec->my_node->argv[1]);
	if (node)
		envlst_free_node(node);
	dat->envp = set_envp(dat->envlist, dat->envp);
}
