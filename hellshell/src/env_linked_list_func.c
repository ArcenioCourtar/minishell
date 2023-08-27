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
void	envlst_addback(t_envlst *list, t_envlst *new)
{
	while (list->next)
		list = list->next;
	list->next = new;
	new->prev = list;
}

// free target node and connect adjacent nodes
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

// move target node from one list to the other (or to the back of a list
// it's already in if you want)
void	envlst_move_node(t_envlst *node, t_envlst *dst)
{
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	envlst_addback(dst, node);
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
		ft_error(errno, "malloc\n");
		free(new);
		return (NULL);
	}
	new->value = ft_substr(envvar, namesize + 1, new->size - namesize);
	if (new->name == NULL)
	{
		ft_error(errno, "malloc\n");
		free(new->name);
		free(new);
	}
	return (new);
}
