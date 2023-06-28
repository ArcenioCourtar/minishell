/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By:                                              +#+                     */
/*                                                   +#+                      */
/*   Created: Invalid date        by               #+#    #+#                 */
/*   Updated: 2023/06/27 13:43:45 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "libft.h"
#include "lexer.h"

void	insert_tokens_in_array(char *input, char **tokens, int token_count)
{
	int	i;
	int	j;
	int	start;
	int	curr_char_type;

	i = 0;
	j = 0;
	while (i < token_count)
	{
		curr_char_type = is_delimiter(input[j]);
		if (curr_char_type < 0)
		{
			start = j;
			while (input[j] && is_delimiter(input[j]) < 0)
				j++;
			tokens[i] = ft_substr(input, start, j - start);
			if (!tokens[i])
				ft_error(errno, strerror(errno));
		}
		else if (curr_char_type >= 0)
			insert_non_text_tokens(input, &tokens[i], &j, curr_char_type);
		i++;
	}
	tokens[i] = NULL;
}

int	token_counter(char *input)
{
	int	i;
	int	count;
	int	curr_char_type;

	count = 0;
	i = 0;
	while (input && input[i])
	{
		curr_char_type = is_delimiter(input[i]);
		count++;
		if (curr_char_type < 0)
			while (input[i] && is_delimiter(input[i]) < 0)
				i++;
		else if (curr_char_type == DEL_SPACE)
			while (input[i] && is_delimiter(input[i]) == DEL_SPACE)
				i++;
		else if (curr_char_type >= 0)
			jump_delimiters(input, &i, curr_char_type);
	}
	return (count);
}

char	**lexer(char *input, int *tok_count)
{
	char	**tokens;
	int		token_count;

	token_count = token_counter(input);
	*tok_count = token_count;
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		ft_error(errno, strerror(errno));
	ft_printf("count: %i\n", *tok_count);
	insert_tokens_in_array(input, tokens, token_count);
	return (tokens);
}
