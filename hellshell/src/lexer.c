/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 15:55:15 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/06/26 15:55:15 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	token_counter(char *input);
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

int	token_counter(char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input && input[i])
	{
		if (input[i] != ' ')
		{
			if (input[i] == 34 || input[i] == 39)
			{
				count++;
				i++;
				while (input[i] && input[i] != 34 && input[i] != 39)
					i++;
				if (input[i])
					i++;
			}
			else
			{
				count++;
				while (input[i] && input[i] != ' ')
					i++;
			}
		}
		else
			i++;
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
