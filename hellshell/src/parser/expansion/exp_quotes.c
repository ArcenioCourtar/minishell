/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_quotes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 14:32:13 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/08/21 14:32:13 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"

/**
 * @brief gets the expanded variable
 * @param data pointer to the data struct
 * @param token pointer to the token to expand
 * @param i pointer to the index of the token
 */
static char	*get_var_string(t_data *data, char *token, int *i)
{
	int		start;
	char	*to_expand;
	char	*expanded;

	(*i)++;
	start = *i;
	while (token[*i] && is_valid_var(token[*i]))
		(*i)++;
	to_expand = ft_substr(token, start, (*i) - start);
	if (!to_expand)
		ft_error(errno, strerror(errno));
	expanded = getvar(data, to_expand, true);
	free(to_expand);
	return (expanded);
}

/**
 * @brief gets the expansion of a token if it's a valid variable
 * @param data pointer to the data struct
 * @param token pointer to the token to expand
 * @return pointer to the expanded token or NULL if not found
 */
char	*get_expansion(t_data *data, char *token, int exp_i, int dol_count)
{
	static int	i;
	char		*expanded;

	expanded = NULL;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && is_valid_var(token[i + 1]))
		{
			expanded = get_var_string(data, token, &i);
			break ;
		}
		i++;
	}
	if (exp_i == dol_count - 1)
		i = 0;
	return (expanded);
}

/**
 * @brief initializes three integers to zero
 * @param i1 pointer to the first integer
 * @param i2 pointer to the second integer
 * @param i3 pointer to the third integer
 */
static void	init_ints_zero(int *i1, int *i2, int *i3)
{
	*i1 = 0;
	*i2 = 0;
	*i3 = 0;
}

/**
 * @brief expands the token with the expansions
 * @param token pointer to the token to expand
 * @param expansions array of expansions
 * @return pointer to the expanded token
 */
char	*add_expans_to_token(char *token, char **expansions)
{
	char	*exp_str;
	int		e;
	int		i;
	int		j;

	exp_str = (char *)malloc(sizeof(char) * \
						(exp_strlen(token, expansions) + 1));
	if (!exp_str)
		ft_error(errno, strerror(errno));
	init_ints_zero(&i, &j, &e);
	while (token[j])
	{
		if (token[j] == '$' && token[j + 1] && token[j + 1] != ' ' \
			&& token[j + 1] != '$')
		{
			j++;
			while (token[j] && is_valid_var(token[j]))
				j++;
			cpy_expansion(&exp_str, &i, expansions[e++]);
		}
		else
			exp_str[i++] = token[j++];
	}
	exp_str[i] = '\0';
	return (exp_str);
}

/**
 * @brief expands the variables in a quotes token
 * @param data pointer to the data struct
 * @param token pointer to the token to expand
 */
void	expand_in_quotes(t_data *data, t_toklst *token)
{
	int		i;
	char	**expansions;
	int		dol_count;

	dol_count = count_dollar_signs(token->token);
	if (dol_count == 0)
		return ;
	expansions = (char **)malloc(sizeof(char *) * (dol_count + 1));
	if (!expansions)
		ft_error(errno, strerror(errno));
	i = 0;
	while (i < dol_count)
	{
		expansions[i] = get_expansion(data, token->token, i, dol_count);
		i++;
	}
	expansions[i] = "\0";
	token->token = add_expans_to_token(token->token, expansions);
	add_to_free_lst(data, token->token);
	free(expansions);
}
