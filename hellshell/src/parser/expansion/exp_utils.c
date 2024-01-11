/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/05 10:57:44 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/12/05 10:57:44 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "minishell.h"

/**
 * @brief Checks if there is a heredoc before the dollar
 * @param data The program data struct.
 * @param token The pointer to the token list.
 * @return 1 if an excetion has to be made, 0 if not
 */
int	heredoc_exception(t_data *data, t_toklst **token)
{
	t_toklst	*tmp;

	tmp = *token;
	while (tmp->prev && tmp->prev->type == TOK_SPACE)
		tmp = tmp->prev;
	if (tmp->prev && tmp->prev->type == TOK_HEREDOC)
	{
		if ((*token)->type == TOK_DOLLAR)
		{
			if ((*token)->next && (*token)->next->type != TOK_SPACE)
			{
				(*token)->token = ft_strjoin((*token)->token, \
														(*token)->next->token);
				add_to_free_lst(data, (*token)->token);
				*token = (*token)->next;
				token_lstdel_node(token);
			}
			(*token)->type = TOK_NAME;
		}
		if ((*token)->type == TOK_DQUOTE || (*token)->type == TOK_SQUOTE)
			trim_quotes(data, token, TOK_SQUOTE);
		return (1);
	}
	return (0);
}

/**
 * @brief expands the question mark variable
 * @param data pointer to the program data struct
 * @param to_expand pointer to the variable to expand
 * @return pointer to the expanded variable
 */
static char	*expand_question_join(t_data *data, char *to_expand)
{
	char	*expanded;
	char	*exit_code;

	exit_code = getvar(data, "?", false);
	expanded = ft_strjoin(exit_code, to_expand + 1);
	add_to_free_lst(data, expanded);
	return (expanded);
}

/**
 * @brief iterates over the environment list to find the variable to expand
 * @param lst pointer to the environment list
 * @param to_expand pointer to the variable to expand
 * @return pointer to the expanded variable or NULL if not found
 */
static char	*envlst_iter(t_envlst *lst, char *to_expand)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->name[i] && to_expand[i] && lst->name[i] == to_expand[i])
			i++;
		if (lst->name[i] == to_expand[i])
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

/**
 * @brief expands the variable
 * @param data pointer to the program data struct
 * @param to_expand pointer to the variable to expand
 * @param in_quotes true if the variable is in quotes, else false
 * @return pointer to the expanded variable
 */
char	*getvar(t_data *data, char *to_expand, bool in_quotes)
{
	char	*var_value;

	if (to_expand[0] == '?' && to_expand[1] != '\0')
		return (expand_question_join(data, to_expand));
	var_value = envlst_iter(data->envlist, to_expand);
	if (!var_value)
		var_value = envlst_iter(data->exit_code, to_expand);
	if (!var_value)
	{
		if (!in_quotes)
			return ("\0");
		else
		{
			var_value = ft_calloc(1, sizeof(char));
			if (!var_value)
				ft_error(errno, strerror(errno));
			add_to_free_lst(data, var_value);
		}
	}
	return (var_value);
}

/**
 * @brief Checks if the variable value contains spaces
 * @param var_value The value of the variable
 * @return true if the variable value contains spaces, else false
 */
bool	check_for_spaces(char *var_value)
{
	int	i;

	i = 0;
	while (var_value[i])
	{
		if (ft_iswhitespace(var_value[i]))
			return (true);
		i++;
	}
	return (false);
}
