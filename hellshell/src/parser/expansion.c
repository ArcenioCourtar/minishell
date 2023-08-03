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
		if (token[i] == TOK_DOLLAR && token[i + 1] && token[i + 1] != ' ') //is that all??
			return (true);
		i++;
	}
	return (false);
}


// WHAT'S BELOW IS NOT IN USE YET
void	expand_in_quotes(t_toklst *token)
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
		while (token->token[i] && token->token[i] != ' ' && token->token[i] != '$')
			i++;
		
		to_expand = ft_substr(token->token, start, i - start);
		//add_to_varlst(to_expand);
		ft_printf("var to expand: %s\n", to_expand);
	}
}

void	expansion(t_toklst **token)
{
	if ((*token)->type == TOK_DQUOTE)
	{
		expand_in_quotes(*token);
	}
	else if ((*token)->type == TOK_DOLLAR)
	{
		if (!(*token)->next || (*token)->next->type == TOK_SPACE)
			(*token)->type = TOK_NAME;
		else
		{
			// expand;
			ft_printf("var to expand: %s\n", (*token)->next->token);
		}
	}
}
