/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_quotes_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/22 13:30:59 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/22 13:30:59 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"

int	count_dollar_signs(char *token)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && !ft_iswhitespace(token[i + 1]) \
		&& (ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
		{
			count++;
			if (token[i + 1] == '$')
				i++;
		}
		i++;
	}
	return (count);
}

int	exp_strlen(char *token, char **expansions)
{
	int	i;
	int	len;
	int	e;

	i = 0;
	len = 0;
	e = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && token[i + 1] != ' ' \
			&& token[i + 1] != '$')
		{
			i++;
			while (token[i] && token[i] != ' ' && token[i] != '$')
				i++;
			len += ft_strlen(expansions[e]);
			e++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	cpy_expansion(char **exp_str, int *i, char *expansion)
{
	int	j;

	j = 0;
	while (expansion[j])
	{
		(*exp_str)[*i] = expansion[j];
		(*i)++;
		j++;
	}
}
