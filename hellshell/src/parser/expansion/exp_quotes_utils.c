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

#include "libft.h"
#include <stdbool.h>

/**
 * @brief checks if a character is a valid variable character
 * @param c character to check
 * @return true if the character is a valid variable character, else false
 */
bool	is_valid_var(char c)
{
	if (!ft_iswhitespace(c) && (ft_isalnum(c) || c == '_' || c == '?'))
		return (true);
	return (false);
}

/**
 * @brief counts the number of dollar signs in a token
 * @param token pointer to the token to check
 * @return number of dollar signs
 */
int	count_dollar_signs(char *token)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && is_valid_var(token[i + 1]))
		{
			count++;
			if (token[i + 1] == '$')
				i++;
		}
		i++;
	}
	return (count);
}

/**
 * @brief counts the length of the expanded string
 * @param token pointer to the token to expand
 * @param expansions array of expansions
 * @return length of the expanded string
 */
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
		if (token[i] == '$' && token[i + 1] && is_valid_var(token[i + 1]))
		{
			i++;
			while (token[i] && is_valid_var(token[i]))
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

/**
 * @brief copies an expansion to the expanded string
 * @param exp_str pointer to the array of expanded strings
 * @param i pointer to the index of the expanded string
 * @param expansion pointer to the expansion to copy
 */
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
