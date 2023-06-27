/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/27 13:43:45 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/27 13:43:45 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "lexer.h"

/** plan
 * token_counter
 * malloc
 * insert tokens in array
 */

int		token_counter(char *input);
void	insert_tokens(char *input, char **tokens, int token_count);

char	**lexer(char *input)
{
	char	**tokens;
	int		token_count;

	token_count = token_counter(input);
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		ft_error(errno, strerror(errno));
	insert_tokens(input, tokens, token_count);
	return (tokens);
}

static int	is_delimiter(char c)
{
	int			i;
	static int	delimiter[7] = {TOK_DQUOTE, TOK_SQUOTE, TOK_PIPE, \
								TOK_DOLLAR, TOK_REDIN, TOK_REDOUT, ' '};

	i = 0;
	while (i < 7)
	{
		if (c == delimiter[i])
			return (i);
		i++;
	}
	return (-1);
}

static void	jump_delimiters(int *i, int t, char *input)
{
	if (t == 0)
	{
		(*i)++;
		while (input[*i] && input[*i] != TOK_DQUOTE)
			(*i)++;
	}
	else if (t == 1)
	{
		(*i)++;
		while (input[*i] && input[*i] != TOK_SQUOTE)
			(*i)++;
	}
	else if ((input[*i + 1] && t == 4 && input[*i + 1] == TOK_REDIN) \
			|| (input[*i + 1] && t == 5 && input[*i + 1] == TOK_REDOUT))
		(*i)++;
	(*i)++;
}

int	token_counter(char *input)
{
	int	i;
	int	count;
	int	t;

	count = 0;
	i = 0;
	while (input && input[i])
	{
		t = is_delimiter(input[i]);
		if (t < 0)
		{
			count++;
			while (input[i] && is_delimiter(input[i]) < 0)
				i++;
		}
		else if (t == 6)
			while (is_delimiter(input[i]) == 6)
				i++;
		else if (t >= 0)
		{
			count++;
			jump_delimiters(&i, t, input);
		}
	}
	return (count);
}

void	insert_tokens(char *input, char **tokens, int token_count)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (i < token_count)
	{
		if (input[j] != ' ')
		{
			start = j;
			if (input[j] == 34 || input[j] == 39)
			{
				j++;
				while (input[j] && input[j] != 34 && input[j] != 39)
					j++;
				j++;
				tokens[i] = ft_substr(input, start, j - start);
			}
			else
			{
				while (input[j] && input[j] != ' ')
					j++;
				tokens[i] = ft_substr(input, start, j - start);
			}
			if (!tokens[i])
				ft_error(errno, strerror(errno));
			i++;
		}
		while (input[j] && input[j] == ' ')
			j++;
	}
	tokens[i] = NULL;
}
