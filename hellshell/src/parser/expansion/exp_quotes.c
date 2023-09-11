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

static char	*get_var_string(t_data *data, char *token, int *i)
{
	int		start;
	char	*to_expand;
	char	*expanded;

	(*i)++;
	start = *i;
	while (token[*i] && token[*i] != ' ' && token[*i] != '$')
		(*i)++;
	to_expand = ft_substr(token, start, (*i) - start);
	if (!to_expand)
		ft_error(errno, strerror(errno));
	expanded = getvar(data, to_expand);
	free(to_expand);
	if (!token[*i])
		*i = 0;
	return (expanded);
}

char	*get_expansion(t_data *data, char *token)
{
	static int	i;
	char		*expanded;

	expanded = NULL;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] && !ft_iswhitespace(token[i + 1]) \
		&& (ft_isalnum(token[i + 1]) || token[i + 1] == '_'))
		{
			expanded = get_var_string(data, token, &i);
			break ;
		}
		i++;
	}
	return (expanded);
}

static void	init_ints_zero(int *i1, int *i2, int *i3)
{
	*i1 = 0;
	*i2 = 0;
	*i3 = 0;
}

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
			while (token[j] && token[j] != ' ' && token[j] != '$')
				j++;
			cpy_expansion(&exp_str, &i, expansions[e++]);
		}
		else
			exp_str[i++] = token[j++];
	}
	exp_str[i] = '\0';
	return (exp_str);
}

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
		expansions[i] = get_expansion(data, token->token);
		i++;
	}
	expansions[i] = "\0";
	token->token = add_expans_to_token(token->token, expansions);
}
