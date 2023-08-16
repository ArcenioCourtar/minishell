/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
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

static char	*getvar(t_data *data, char *to_expand)
{
	char	*var_value;

	var_value = envlst_iter(data->envlist, to_expand);
	if (!var_value)
		var_value = envlst_iter(data->varlist, to_expand);
	if (var_value)
		return (var_value);
	else
		return ("");
}

static void	expand_in_quotes(t_data *data, t_toklst *token)
{
	int		i;
	int		start;
	char	*to_expand;

	i = 0;
	while (token->token[i])
	{
		while (token->token[i] && token->token[i] != TOK_DOLLAR)
			i++;
		if (!token->token[i])
			break ;
		i++;
		start = i;
		while (token->token[i] && token->token[i] != ' ' \
										&& token->token[i] != '$')
			i++;
		to_expand = ft_substr(token->token, start, i - start);
		if (!to_expand)
			ft_error(errno, strerror(errno));
		token->token = getvar(data, to_expand);
		free(to_expand);
	}
}

void	expansion(t_data *data, t_toklst **token)
{
	if ((*token)->type == TOK_DQUOTE)
	{
		expand_in_quotes(data, *token);
	}
	else if ((*token)->type == TOK_DOLLAR)
	{
		if (!(*token)->next || (*token)->next->type == TOK_SPACE)
			(*token)->type = TOK_NAME;
		else if ((*token)->next->type == TOK_DQUOTE \
					|| (*token)->next->type == TOK_SQUOTE)
			toklst_del_node(token);
		else
		{
			(*token)->next->token = getvar(data, (*token)->next->token);
			toklst_del_node(token);
			if ((*token)->type != TOK_SPACE)
				quote_join(token, false);
		}
	}
}
