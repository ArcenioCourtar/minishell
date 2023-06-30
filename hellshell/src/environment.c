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

t_envlist	*newnode_env(char *envvar)
{
	t_envlist	*new;
	size_t		namesize;

	new = malloc(sizeof(t_envlist));
	if (new == NULL)
		return (NULL);
	if (ft_strchr(envvar, '=') == 0)
		new->size = ft_strlen(envvar) + 1;
	else
		new->size = ft_strlen(envvar);
	new->next = NULL;
	new->prev = NULL;
	if (ft_strchr(envvar, '=') == 0)
		namesize = new->size - 1;
	else
		namesize = ft_strchr(envvar, '=') - envvar;
	new->name = ft_substr(envvar, 0, namesize);
	if (new->name == NULL)
		ft_error(errno, "malloc\n");
	new->value = ft_substr(envvar, namesize + 1, new->size - namesize);
	if (new->name == NULL)
		ft_error(errno, "malloc\n");
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
			ft_error(errno, "malloc\n");
		next->next = new;
		new->prev = next;
		next = next->next;
		i++;
	}
	return (start);
}

int	envlist_nodecount(t_envlist *start)
{
	t_envlist	*tmp;
	int			i;

	i = 0;
	tmp = start;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static void	cpy_contents(char *new, t_envlist *node)
{
	int	len_name;
	int	len_val;

	len_name = ft_strlen(node->name);
	len_val = ft_strlen(node->value);
	ft_memcpy(new, node->name, len_name);
	new[len_name] = '=';
	ft_memcpy(new + len_name + 1, node->value, len_val);
	new[len_name + len_val + 1] = '\0';
}

// Assuming the last address is set to NULL
void	free_doubleptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	**set_envp(t_envlist *envlist, char **envp)
{
	char	**new;
	int		count;
	int		i;

	if (envp != NULL)
		free_doubleptr(envp);
	count = envlist_nodecount(envlist);
	new = malloc(sizeof(char *) * (count + 1));
	if (!new)
		ft_error(errno, "malloc\n");
	i = 0;
	while (envlist)
	{
		new[i] = malloc(sizeof(char) * (envlist->size + 1));
		if (!new[i])
			ft_error(errno, "malloc\n");
		cpy_contents(new[i], envlist);
		envlist = envlist->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}
