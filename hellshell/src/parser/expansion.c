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

// void	expand_from_varlst(t_data *data, t_toklst *token, char *to_expand)
// {
// 	t_envlst	*tmp;

// 	tmp = data->varlist;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->name, to_expand, ))
// 			ft_printf("variable found\n");
// 		tmp = tmp->next;
// 	}
// }

void	expand_in_quotes(t_data *data, t_toklst *token)
{
	int		i;
	int		start;
	char	*to_expand;

	i = 0;
	while (token->token[i])
	{
		while (token->token[i] != TOK_DOLLAR)
			i++;
		i++;
		start = i;
		while (token->token[i] && token->token[i] != ' ' \
										&& token->token[i] != '$')
			i++;
		to_expand = ft_substr(token->token, start, i - start);
		//find_in_varlist_and_expand(data, token, to_expand)
		ft_printf("tokcount: %i\nvar to expand: %s\n", data->tok_count, to_expand);
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
			//find_in_varlist_and_expand(data, token, (*token)->next->token)
			ft_printf("var to expand: $%s\n", (*token)->next->token);
		}
	}
}
