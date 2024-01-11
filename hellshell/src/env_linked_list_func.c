/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_linked_list_func.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 13:03:56 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/27 13:03:56 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

// add node to the back of list
void	envlst_addback(t_envlst **list, t_envlst *new)
{
	t_envlst	*tmp;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

// free target node and connect adjacent nodes
void	envlst_free_node(t_envlst **del)
{
	if ((*del)->next)
		(*del)->next->prev = (*del)->prev;
	if ((*del)->prev)
		(*del)->prev->next = (*del)->next;
	free((*del)->name);
	free((*del)->value);
	free((*del));
	*del = NULL;
}

void	envlst_free_node_new(t_envlst **list, t_envlst *del)
{
	if (del == NULL || *list == NULL)
		return ;
	if (del == *list)
		*list = del->next;
	if (del->next)
		del->next->prev = del->prev;
	if (del->prev)
		del->prev->next = del->next;
	free(del->name);
	free(del->value);
	free(del);
}

// take a string in a "name=value" format and create a new node
t_envlst	*newnode_env(char *envvar)
{
	t_envlst	*new;
	size_t		namesize;

	new = malloc(sizeof(t_envlst));
	if (new == NULL)
		return (NULL);
	new->size = ft_strlen(envvar);
	new->next = NULL;
	new->prev = NULL;
	namesize = ft_strchr(envvar, '=') - envvar;
	new->name = ft_substr(envvar, 0, namesize);
	if (new->name == NULL)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_substr(envvar, namesize + 1, new->size - namesize);
	if (new->name == NULL)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	return (new);
}

// create a new node with "name" and "value"
t_envlst	*newnode_env_alt(char *name, char *value)
{
	t_envlst	*new;

	new = malloc(sizeof(t_envlst));
	if (new == NULL)
		return (NULL);
	new->size = ft_strlen(name) + ft_strlen(value) + 1;
	new->next = NULL;
	new->prev = NULL;
	new->name = ft_substr(name, 0, ft_strlen(name));
	if (new->name == NULL)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_substr(value, 0, ft_strlen(value));
	if (new->name == NULL)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	return (new);
}
