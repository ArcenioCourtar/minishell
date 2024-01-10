/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 12:24:16 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/03 12:24:16 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"

/**
 * @brief checks if a token contains a dollar sign
 * @param token pointer to the token to check
 * @return true if the token contains a dollar sign, else false
 */
bool	check_for_dollar(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == TOK_DOLLAR && token[i + 1] && token[i + 1] != ' ')
			return (true);
		i++;
	}
	return (false);
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
 * @brief expands the question mark variable
 * @param data pointer to the program data struct
 * @param to_expand pointer to the variable to expand
 * @return pointer to the expanded variable
 */
char	*expand_question_join(t_data *data, char *to_expand)
{
	char	*expanded;
	char	*exit_code;

	exit_code = getvar(data, "?", false);
	expanded = ft_strjoin(exit_code, to_expand + 1);
	add_to_free_lst(data, expanded);
	return (expanded);
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
 * @brief expands the variable in a token
 * @param data pointer to the program data struct
 * @param token pointer to the token to expand
 */
void	expansion(t_data *data, t_toklst **token)
{
	if (heredoc_exception(data, token))
		return ;
	if ((*token)->type == TOK_DQUOTE)
		expand_in_quotes(data, *token);
	else if ((*token)->type == TOK_DOLLAR)
	{
		if (!(*token)->next || (*token)->next->type == TOK_SPACE)
		{
			(*token)->type = TOK_NAME;
			*token = (*token)->next;
		}
		else if ((*token)->next->type == TOK_DQUOTE \
					|| (*token)->next->type == TOK_SQUOTE)
			token_lstdel_node(token);
		else
		{
			(*token)->next->token = getvar(data, (*token)->next->token, false);
			token_lstdel_node(token);
			if (ft_strlen((*token)->token) == 0)
				(*token)->type = TOK_INVALID;
			if ((*token) && (*token)->prev && (*token)->prev->type \
			!= TOK_SPACE && !is_redirect((*token)->prev->type))
				quote_join(data, token, true);
		}
	}
}
