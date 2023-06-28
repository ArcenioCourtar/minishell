/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/27 16:29:08 by acourtar      #+#    #+#                 */
/*   Updated: 2023/06/27 16:29:08 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>

t_envlist	*newnode_env(char *envp)
{
	t_envlist	*new;
	size_t		namesize;

	new = malloc(sizeof(t_envlist));
	if (new == NULL)
		return (NULL);
	new->size = ft_strlen(envp);
	new->next = NULL;
	namesize = ft_strchr(envp, '=') - envp;
	new->name = ft_substr(envp, 0, namesize);
	if (new->name == NULL)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_substr(envp, namesize + 1, new->size - namesize);
	if (new->name == NULL)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	return (new);
}

t_envlist	*init_envlist(char **envp)
{
	t_envlist	*start;
	t_envlist	*new;
	t_envlist	*next;
	int			i;

	i = 0;
	start = newnode_env(envp[i]);
	if (!start)
		return (NULL);
	i++;
	next = start;
	while (envp[i])
	{
		new = newnode_env(envp[i]);
		if (!new)
		{
			// freeing
			return (NULL);
		}
		next->next = new;
		next = next->next;
		i++;
	}
	return (start);
}
