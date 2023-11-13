/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env_variable_helpers.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 12:59:18 by acourtar      #+#    #+#                 */
/*   Updated: 2023/08/27 12:59:18 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft.h"
#include "builtins.h"
#include <readline/readline.h>
#include <readline/history.h>

// Checks target list for existence of variable var.
// var can be both just a name or "NAME=value".
t_envlst	*check_var_existence(t_envlst *list, char *var)
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

// Change the value of a an already existing node.
// var has to come in the format of "NAME=VALUE".
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

// Change the value of a an already existing node.
// Just pass along the node you want to change and the value it needs to have.
bool	change_existing_val_alt(t_envlst *node, char *val)
{
	int	len;

	free(node->value);
	len = ft_strlen(val);
	node->value = malloc(len + 1);
	if (!node->value)
		return (false);
	ft_strlcpy(node->value, val, len + 1);
	node->size = ft_strlen(node->name) + len + 1;
	return (true);
}
